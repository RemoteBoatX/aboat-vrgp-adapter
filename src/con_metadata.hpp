#pragma once

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

#include <iostream>
#include <vector>


/**
 * Has handlers for different events.
 */
class connection_metadata {

public:

    typedef websocketpp::client<websocketpp::config::asio_client> client_endpoint;

    /**
     * Handler for on open.
     */
    void on_open(client_endpoint * c, websocketpp::connection_hdl handler);

    /**
     * Handler for on fail.
     */
    void on_fail(client_endpoint * c, websocketpp::connection_hdl handler);

    /**
     * Handler for on close.
     */
    void on_close(client_endpoint * c, websocketpp::connection_hdl handler);

    /**
     * Handler for the message.
     */
    void on_message(websocketpp::connection_hdl handler, client_endpoint::message_ptr msg);

};
