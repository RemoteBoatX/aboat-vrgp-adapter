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
typedef websocketpp::client<websocketpp::config::asio_client> configured_endpoint;


/**
 * Websocket setup wrapper for an endpoint configuration.
 *
 * Holds a configured endpoint, a list of all connections, and sets up the
 * background thread for websocket connections.
 *
 * Handles initialization and setting up the thread.
 */
class websocket_endpoint_wrapper {

public:

    websocket_endpoint_wrapper();
    ~websocket_endpoint_wrapper();

    /**
     * Open a new WebSocket connection to the given URI.
     *
     * @param uri The given URI to connect to.
     */
    int connect(std::string const & uri);

    /**
     * Close a WebSocket connection.
     *
     * @param id The given id of the connection.
     * @param code The status code reason of the connection closure.
     * @param reason The text with the reason of the connection closure.
     */
    void close(int id, websocketpp::close::status::value code, std::string reason);

    /**
     * Returns metadata about a specific connection, or an empty metadata
     * pointer if the connection id is not available.
     *
     * @id The given id of the connection.
     */
    connection_metadata::ptr get_metadata(int id) const;

private:

    /**
     * Incrementing id's for connections.
     */
    int _next_id;

    /**
     * The configured endpoint. Additional configuration is set up in the
     * constructor.
     */
    configured_endpoint _endpoint;

    /**
     * A pointer to the background thread used for the websocket connections.
     */
    websocketpp::lib::shared_ptr<websocketpp::lib::thread> _thread;


    /**
     * A list of the connections.
     */
    typedef std::map<int, connection_metadata::ptr> con_list;

    con_list _connection_list;
};
