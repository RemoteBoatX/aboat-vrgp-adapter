#pragma once

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <sstream>

#include "con_metadata.hpp"

/**
 * Create a typedef for the endpoint config.
 *
 * `websocketpp::client` is an endpoint, which is configured using the
 * `websocketpp::config::asio_client`, which is a default config, with not TLS
 * support.
 *
 * TODO change later to TLS config, and change other stock parameters on the
 * endpoint according to the TLS needs.
 *
 * @see https://docs.websocketpp.org/md_tutorials_utility_client_utility_client.html (step 2)
 *
 */
typedef websocketpp::client<websocketpp::config::asio_client> client_endpoint;


/**
 * Websocket setup wrapper for an endpoint configuration.
 *
 * Holds a configured endpoint and a connection to the VRGP service.
 *
 * Handles initialization and setting up the thread.
 */
class websocket_endpoint_wrapper {

public:

    /**
     * Open a new WebSocket connection to the given URI of the VRGP service.
     *
     * @param uri The given URI to connect to.
     */
    websocket_endpoint_wrapper(std::string const & uri);

    ~websocket_endpoint_wrapper();

    /**
     * Send a message through the WebSocket connection.
     *
     * @param message The message to send.
     */
    void send(std::string message);

private:

    /**
     * The configured endpoint. Additional configuration is set up in the
     * constructor.
     */
    client_endpoint _client;

    /**
     * The connection handler, used for sending messages etc.
     */
    websocketpp::connection_hdl _handler;

    /**
     * The VRGP connection.
     */
    websocketpp::lib::shared_ptr<connection_metadata> _connection;

    /**
     * Thread of the connection.
     */
    websocketpp::lib::shared_ptr<websocketpp::lib::thread> _thread;

};
