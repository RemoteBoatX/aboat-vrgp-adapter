#pragma once

#include <websocketpp/common/functional.hpp>
#include <websocketpp/common/memory.hpp>

#include <nlohmann/json.hpp>

#include "cluon_complete.hpp"
#include "connection_messages.hpp"

#include <iostream>
#include <string>
#include <cstdlib>
#include <atomic>

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
     * @param done Wether the OpenDLV handler should be stopped or not.
     */
    opendlv_handler(websocketpp::lib::function<void (std::string)> send_func, std::atomic_bool& done);
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

    /**
     * The session number of the OpenDLV messages.
     */
    uint16_t _od4_session;

    /**
     * Whether or not the OpenDLV handler should stop running.
     */
    std::atomic_bool& _done;

};

} // namespace vrgp_adapter
