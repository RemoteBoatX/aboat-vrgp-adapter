#pragma once

#include <string>

#ifdef BUILD_DEBUG
 #include <cassert>
#endif

#include "websocket_client.hpp"
#include "opendlv_handler.hpp"


namespace vrgp_adapter {

/**
 * The top class of the adapter service.
 *
 * Takes care of getting/serving the sensor data from the Åboat and processing
 * web socket requests from the VRGP service.
 */
class adapter_manager {

public:

    adapter_manager(std::string const & url);
    ~adapter_manager();

    /**
     * Run the WebSocket and OpenDLV threads.
     *
     * <b>Note:</b> It's important that the threads are not started in the
     * constructor above, but rather here, as race conditions could
     * theoretically happen.
     */
    void run();

    /**
     * Send message function. Passed to the opendlv handler as a forwarder
     * (proxy).
     */
    void send(std::string msg) {
#ifdef BUILD_DEBUG
        assert(_client_ptr != nullptr);
#endif
        _client_ptr->send(msg);
    }

    /**
     * Receive message function. Passed to the websocket client as a forwarder
     * (proxy).
     */
    void on_receive(std::string msg) {
#ifdef BUILD_DEBUG
        assert(_opendlv_handler_ptr != nullptr);
#endif
        _opendlv_handler_ptr->on_receive(msg);
    }

private:

    /**
     * The WebSocket client endpoint. Used to send and retrieve messages from
     * the VRGP service.
     */
    vrgp_adapter::websocket_client::ptr _client_ptr;

    /**
     * The thread running the WebSocket connection.
     */
    websocketpp::lib::shared_ptr<websocketpp::lib::thread> _client_thread_ptr;

    /**
     * The OpenDLV handler. Used to communicate with the vessel.
     */
    vrgp_adapter::opendlv_handler::ptr _opendlv_handler_ptr;

    /**
     * The thread running the OpenDLV handler.
     */
    websocketpp::lib::shared_ptr<websocketpp::lib::thread> _opendlv_handler_thread_ptr;

};

} // namespace vrgp_adapter
