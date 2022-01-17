#include "endpoint_wrapper.hpp"
#include <cassert>

websocket_endpoint_wrapper::websocket_endpoint_wrapper(std::string const & uri) {

    try {

        // set logging to be pretty verbose (everything except message payloads)
        _client.set_access_channels(websocketpp::log::alevel::all);
        _client.clear_access_channels(websocketpp::log::alevel::frame_payload);

        // init ASIO
        _client.init_asio();

        websocketpp::lib::error_code ec;

        // acquire a connection ptr, in order to configure the connection
        client_endpoint::connection_ptr con = _client.get_connection(uri, ec);

        if (ec) {
            std::cout << "> Connection initialization error: " << ec.message() << std::endl;
            throw ec;
        }

        websocketpp::lib::shared_ptr<connection_metadata> metadata_ptr(new connection_metadata());
        _connection = metadata_ptr;
        _handler = con->get_handle();

        // run on open connection
        con->set_open_handler(websocketpp::lib::bind(
            &connection_metadata::on_open,
            metadata_ptr,
            &_client,
            websocketpp::lib::placeholders::_1
        ));

        // run on message
        con->set_message_handler(websocketpp::lib::bind(
            &connection_metadata::on_message,
            metadata_ptr,
            websocketpp::lib::placeholders::_1,
            websocketpp::lib::placeholders::_2
        ));

        // in the end, open the connection
        _client.connect(con);

        // init a thread to take care of the connection, leave main thread open for
        // other stuff
        _thread.reset(new websocketpp::lib::thread(&client_endpoint::run, &_client));

    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    }
}

websocket_endpoint_wrapper::~websocket_endpoint_wrapper() {

    // stop the connection thread
    _thread->join();
}

void websocket_endpoint_wrapper::send(std::string message) {

    if (_connection == nullptr) {
        std::cout << "> No active connection." << std::endl;
        return;
    }

    websocketpp::lib::error_code ec;

    std::cout << "sending.." << std::endl;

    _client.send(_handler, message, websocketpp::frame::opcode::text, ec);

    std::cout << "sent" << std::endl;

    if (ec) {
        std::cout << "> Error sending message: " << ec.message() << std::endl;
    }
}
