#pragma once

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

#include <string>
#include <atomic>


namespace vrgp_adapter {

/**
 * The WebSocket client. Takes care of the low-level WebSocket library stuff,
 * including setting up, sending and receiving messages.
 */
class websocket_client {

public:

    // just a typedef, be nice and spread happiness
    typedef websocketpp::lib::shared_ptr<websocket_client> ptr;

    /**
     * Initialize the connection, set logging channels, configure the message
     * handlers.
     *
     * @param url The url of the VRGP service.
     * @param on_receive_func The <code>on_receive</code> function that should
     *                  be called when receiving a message.
     * @param done Whether the WebSocket connection should be closed or not.
     * @throws websocketpp::exception When the connection couldn't be opened.
     */
    websocket_client(
            std::string const & url,
            websocketpp::lib::function<void (std::string)> on_receive_func,
            std::atomic_bool& done);

    ~websocket_client();

    /**
     * Start the event loop running the WebSocket client.
     *
     * This is a <b>blocking</b> event.
     */
    void run();

    /**
     * Sends messages through the WebSocket connection.
     *
     * @param message The message to send.
     * @throws websocketpp::exception When the message couldn't be send.
     */
    void send(std::string message);

    /**
     * Takes care of the connection <code>on_message</code>. Receives a message,
     * processes it and sends it further along the pipeline using the
     * <code>on_receive</code> method passed in as a parameter.
     *
     * @param on_receive The method used to pass along the message.
     * @param handler The connection handler.
     * @param msg The message received on the WebSocket network.
     * @throws websocketpp::exception When the message couldn't be decoded.
     */
    void on_message(
            websocketpp::lib::function<void (std::string)> on_receive,
            websocketpp::connection_hdl handler,
            websocketpp::client<websocketpp::config::asio_client>::message_ptr msg);

    /**
     * Run on connection open.
     *
     * Sets the ready state of the connection.
     *
     * @param handler The connection handler.
     */
    void on_open(websocketpp::connection_hdl handler);

private:

    /**
     * The low-level WebSocket++ library endpoint.
     *
     * TODO(alexghergh): For now, the low-level config is set to async, no
     * TLS. In the future, should change to TLS.
     */
    websocketpp::client<websocketpp::config::asio_client> _connection;

    /**
     * The connection handler (or identifier).
     */
    websocketpp::connection_hdl _handler;

    /**
     * Whether the WebSocket connection should be closed or not.
     */
    std::atomic_bool& _done;

    /**
     * Whether the WebSocket connection is ready or not.
     */
    std::atomic_bool _readyState;

};

} // namespace vrgp_adapter
