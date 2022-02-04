#include "opendlv_handler.hpp"
#include "cluon-complete.hpp"
#include "mymessages.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;         


namespace vrgp_adapter {

json componentInfo_json;
json actuatorInfo_json;
json sensorInfo_json;
json signalInfo_json;

opendlv_handler::opendlv_handler(websocketpp::lib::function<void (std::string)> send_func) {
    _send = send_func;
}

opendlv_handler::~opendlv_handler() {
}

opendlv_handler::run() {

    // should continuously loop and process any message from the boat side,
    // through opendlv --> Assume it's only one kind of method

    cluon::OD4Session od4{150};

    if(od4.isRunning()) {
        auto onSensorInfo = [](cluon::data::Envelope &&env){
                        
            opendlv::body::SensorInfo msg = cluon::extractMessage<opendlv::body::SensorInfo>(std::move(env));

            if(msg.description() != NULL) {signalInfo["description"] = msg.description();}
            if(msg.x() != NULL) {signalInfo["x"] = msg.x();}
            if(msg.y() != NULL) {signalInfo["y"] = msg.y();}
            if(msg.z() != NULL) {signalInfo["z"] = msg.z();}
            if(msg.signalId() != NULL) {signalInfo["signalId"] = msg.signalId();}
            if(msg.accuracyStd() != NULL) {signalInfo["accuracyStd"] = msg.accuracyStd();}
            if(msg.minFrequency() != NULL) {signalInfo["minFrequency"] = msg.minFrequency();}
        };
    }

    od4.dataTrigger(opendlv::body::SensorInfo::ID(), onSensorInfo);

}

std::string opendlv_handler::on_receive(std::string msg) {

    // should receive a message, decode it, and act accordingly (i.e. get the
    // data from the vessel etc.) --> It's JSON in the specification    

    std::string requested_dev;
    std::string acquired_dev;

    json json_msg = json::parse(msg);

    /*
    * Maybe use switch for these cases
    */
    if (json_msg.contains("request")) {
        requested_dev = json_msg.at("request");
        if(requested_dev.compare("SensorInfo") != 0) {
            // Send "file_" + opendlv::body::SensorInfo:ID() + ".json"
        }
    } else if (json_msg.contains("acquire")) {
        acquired_dev = json_msg.at("acquire");
        if(acquired_dev.compare("SensorInfo") != 0) {
            return  sensorInfo_json.dump();
        }
    }
}


/*
* This gives a list of the available devices by their IDs,
* not possible to get their names from the message itself
*/
int find_devices() {
    
    json devices_array;
    
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

} // namespace vrgp_adapter
