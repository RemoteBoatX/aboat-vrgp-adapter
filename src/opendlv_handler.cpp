#include "opendlv_handler.hpp"

namespace vrgp_adapter {

state stateInfo;

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
            json sensorInfo_json;

            if(msg.description() != NULL) {signalInfo["description"] = msg.description();}
            if(msg.x() != NULL) {signalInfo["x"] = msg.x();}
            if(msg.y() != NULL) {signalInfo["y"] = msg.y();}
            if(msg.z() != NULL) {signalInfo["z"] = msg.z();}
            if(msg.signalId() != NULL) {signalInfo["signalId"] = msg.signalId();}
            if(msg.accuracyStd() != NULL) {signalInfo["accuracyStd"] = msg.accuracyStd();}
            if(msg.minFrequency() != NULL) {signalInfo["minFrequency"] = msg.minFrequency();}
        
            stateInfo.setSensorInfo(sensorInfo_json);
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

    if (json_msg.contains("request")) {
        requested_dev = json_msg.at("request");
        if(requested_dev.compare("SensorInfo") != 0) {
            return stateInfo.getSensorInfo();
        }
    } else if (json_msg.contains("acquire")) {
        acquired_dev = json_msg.at("acquire");
        if(acquired_dev.compare("SensorInfo") != 0) {
            std::out << sensorInfo_json.dump() << std::endl;
        }
    }
}
} // namespace vrgp_adapter
