#include "websocket_client.hpp"

namespace vrgp_adapter {

websocket_client::websocket_client(
        std::string const & url,
        std::function<void (std::string)> on_receive_func) {

    // set logging to be pretty verbose (everything except message payloads)
    _connection.set_access_channels(websocketpp::log::alevel::all);
#ifndef BUILD_DEBUG
    _connection.clear_access_channels(websocketpp::log::alevel::frame_payload);
#endif

    // init ASIO
    _connection.init_asio();

    websocketpp::lib::error_code ec;

    // acquire a connection ptr, in order to configure the connection
    websocketpp::client<websocketpp::config::asio_client>::connection_ptr
        con_ptr = _connection.get_connection(url, ec);

    if (ec) {
        throw websocketpp::exception(
                "Failed to open connection to " + url + ": " + ec.message()
                + ". Aborting...", websocketpp::error::con_creation_failed);
    }

    // acquire the connection handler
    _handler = con_ptr->get_handle();

    // callback to run on message
    con_ptr->set_message_handler(websocketpp::lib::bind(
        &vrgp_adapter::websocket_client::on_message,
        this,
        on_receive_func,
        websocketpp::lib::placeholders::_1,
        websocketpp::lib::placeholders::_2
    ));

    // after configuring the connection, finally connect to the remote endpoint
    // note that this only requests a connection
    // no actual network messages are exchanged until the event loop is
    // started in the `run()` method below
    _connection.connect(con_ptr);

}

websocket_client::~websocket_client() {

}

void websocket_client::run() {
    // start the event loop
    _connection.run();
}

void websocket_client::send(std::string msg) {

    websocketpp::lib::error_code ec;

    _connection.send(_handler, msg, websocketpp::frame::opcode::text, ec);

    if (ec) {
        throw websocketpp::exception(
                "Error sending message: " + ec.message(),
                websocketpp::error::invalid_state);
    }
}

void on_message(
        std::function<void (std::string)> on_receive,
        websocketpp::connection_hdl handler,
        websocketpp::client<websocketpp::config::asio_client>::message_ptr msg) {

    std::string message;

    if (msg->get_opcode() == websocketpp::frame::opcode::text) {
        message = msg->get_payload();
    } else if (msg->get_opcode() == websocketpp::frame::opcode::binary) {
        message = websocketpp::utility::to_hex(msg->get_payload());
    } else {
        throw websocketpp::exception(
                "The message was neither text nor binary!",
                websocketpp::error::payload_violation);
    }

    on_receive(message);
}

} // namespace vrgp_adapter
