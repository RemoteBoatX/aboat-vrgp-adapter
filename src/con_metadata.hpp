#pragma once

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

#include <iostream>

/**
 * Holds information about a specific connection.
 *
 * Also has handlers for the connection on open and on fail requests.
 */
class connection_metadata {

public:

    /**
     * Shared pointer for connection metadata.
     */
    typedef websocketpp::lib::shared_ptr<connection_metadata> ptr;

    /**
     * @see endpoint_wrapper.hpp
     */
    typedef websocketpp::client<websocketpp::config::asio_client> configured_endpoint;

    connection_metadata(int id, websocketpp::connection_hdl handler, std::string uri);

    /**
     * Handler for on open.
     */
    void on_open(configured_endpoint * c, websocketpp::connection_hdl handler);

    /**
     * Handler for on fail.
     */
    void on_fail(configured_endpoint * c, websocketpp::connection_hdl handler);

    /**
     * Standard toString method.
     *
     * Outputs information about the metadata of a specific connection.
     */
    friend std::ostream & operator<< (std::ostream & out, connection_metadata const & data);

private:

    int _id;

    websocketpp::connection_hdl _handler;

    std::string _status;

    std::string _uri;

    std::string _server;

    std::string _error_reason;

};
