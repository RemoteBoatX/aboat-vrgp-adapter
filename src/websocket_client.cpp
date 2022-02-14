#include "websocket_client.hpp"

namespace vrgp_adapter {

websocket_client::websocket_client(
        std::string const & url,
        websocketpp::lib::function<void (std::string)> on_receive_func,
        std::atomic_bool& done)
    : _done(done) {

    // set logging to be pretty verbose
    _connection.set_access_channels(websocketpp::log::alevel::all);

    // exclude message payload in release builds
    _connection.clear_access_channels(websocketpp::log::alevel::frame_payload);

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

    // since we don't have control over the event loop of the WebSocket client
    // to be able to stop it whenever we want, we need some other form of
    // thread interruption
    //
    // the code below aims to work around this (yes, it is a nasty hack, but the
    // other solution would just be to modify the WebSocket++ library code)
    //
    // what we do is basically set up a new thread that runs along the
    // connection thread, and watches for modification to the '_done' variable; if
    // this is set to true, then we send a WebSocket connection closure message
    // to the VRGP service; the '_done' variable can be set to true from the OpenDLV
    // handler for example; the OpenDLV handler may receive a close message from
    // the boat-side, which would mean that there is no point for the WebSocket
    // handler to run anymore
    //
    // there is an additional variable 'conn_closed'; it is not as important as
    // the '_done' variable; it's role is mostly to control whether or not a
    // WebSocket close message is actually sent; if the VRGP service closes the
    // WebSocket connection for whatever reason, then there is no point in
    // sending a close message from the adapter's WebSocket handler, and so we
    // just close the thread and do nothing else (when 'conn_closed' is set to
    // true); if otherwise the adapter is stopped because of the OpenDLV
    // handler, then we sent a WebSocket close message to the VRGP service
    // normally (when 'conn_closed' is set to false)

    bool conn_closed = false;

    // connection closure thread, monitors the '_done' variable
    // and stops the WebSocket connection thread as needed
    websocketpp::lib::thread conn_close_thr([this, &conn_closed]() {
        while (true) {
            if (_done) {

                if (conn_closed) {
                    break;
                }

                websocketpp::lib::error_code ec;
                std::string reason = "";

                _connection.close(_handler, websocketpp::close::status::normal, reason, ec);

                if (ec) {
                    std::cout << "Error closing websocket connection: " << ec.message() << std::endl;
                }

                break;
            }
        }
    });

    // start the event loop
    _connection.run();

    // important: always set conn_closed true before done
    conn_closed = true;
    _done = true;

    conn_close_thr.join();
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

void websocket_client::on_message(
        websocketpp::lib::function<void (std::string)> on_receive,
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
