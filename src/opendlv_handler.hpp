#pragma once

#include <websocketpp/common/functional.hpp>
#include <websocketpp/common/memory.hpp>

#include <iostream>
#include <string>

#include <chrono>
#include <thread>

#include "cluon-complete.hpp"
#include "mymessages.hpp"
#include "state.cpp"

#include "nlohmann/json.hpp"

using json = nlohmann::json;  


namespace vrgp_adapter {

/**
 * The OpenDLV handler. Takes care of the OpenDLV communication with the
 * vessel.
 */
class opendlv_handler {

public:

    typedef websocketpp::lib::shared_ptr<opendlv_handler> ptr;

    /**
     * Initialize the OpenDLV connection.
     *
     * @param send_func The <code>send</code> function to call when sending messages.
     */
    opendlv_handler(websocketpp::lib::function<void (std::string)> send_func);
    ~opendlv_handler();

    /**
     * Start the event loop running the OpenDLV communication.
     *
     * This is a <b>blocking</b> event.
     */
    void run();

    /**
     * Receive messages from the VRGP service.
     *
     * @param msg The message received.
     */
    void on_receive(std::string msg);

private:

    /**
     * The send function to call when sending a message.
     */
    websocketpp::lib::function<void (std::string)> _send;

};

} // namespace vrgp_adapter
