#include "opendlv_handler.hpp"
#include "cluon-complete.hpp"
#include "mymessages.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <nlohmann/json.hpp>
#include <string>


namespace vrgp_adapter {

opendlv_handler::opendlv_handler(websocketpp::lib::function<void (std::string)> send_func) {
    _send = send_func;
}

opendlv_handler::~opendlv_handler() {
}

void opendlv_handler::run() {
    // TODO(joan) opendlv logic
    // should continuously loop and process any message from the boat side,
    // through opendlv --> Assume it's only one kind of method

    cluon::OD4Session od4{150};

    if(od4.isRunning()) {
        auto onSensorInfo = [](cluon::data::Envelope &&env){
            
            /*
            * This line would be used in case of object creation
            *opendlv::body::SensorInfo msg = cluon::extractMessage<opendlv::body::SensorInfo>(std::move(env));
            */
            std::string file_name = "file_" + std::to_string(env.dataType()) + ".json";
            std::ofstream o(file_name);

            cluon::EnvelopeConverter conv;
            o << conv.getJSONFromEnvelope(env) << std::endl;

            // Maybe create an object in which having the information stored instead of
            // the json file itself (?)
        };
    }


}

void opendlv_handler::on_receive(std::string msg) {
    // TODO(joan) opendlv receive logic
    // should receive a message, decode it, and act accordingly (i.e. get the
    // data from the vessel etc.) --> It's JSON in the specification
}


/*
* This gives a list of the available devices by their IDs,
* not possible to get their names from the message itself
*/
int find_devices() {
    
    nlohmann::json devices_array;
    
    // We open a session and wait for messages to arrive
    // Didn't find the message of request from the Aboat to the MOC                        
    cluon::OD4Session od4{111, [&devices_array](cluon::data::Envelope &&env){                
            
            //TO DO Change to device name if possible
            std::string device_id = std::to_string(env.dataType());
            devices_array["ID_" + device_id] = env.dataType();     
            
            //Writing on the json file
            std::ofstream o("devices.json");
            o << std::setw(4) << devices_array << std::endl;                
    }};

    // Let's wait for 15s to receive messages.
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(15s);

    return(0);
}

int main() {

    find_devices();
    return(0);
}

} // namespace vrgp_adapter
