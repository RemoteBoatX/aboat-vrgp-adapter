#include "opendlv_handler.hpp"

namespace vrgp_adapter {

state stateInfo;

opendlv_handler::opendlv_handler(websocketpp::lib::function<void (std::string)> send_func) {
    _send = send_func;
}

opendlv_handler::~opendlv_handler() {
}

opendlv_handler::run() {

    json conning_msg;
    // We set specific setup for every different odvd message

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

        auto onActuatorInfo = [](cluon::data::Envelope &&env){                    
            opendlv::body::ActuatorInfo msg = cluon::extractMessage<opendlv::body::ActuatorInfo>(std::move(env));
            json actuatorInfo_json;

            if(msg.description() != NULL) {signalInfo["description"] = msg.description();}
            if(msg.x() != NULL) {signalInfo["x"] = msg.x();}
            if(msg.y() != NULL) {signalInfo["y"] = msg.y();}
            if(msg.z() != NULL) {signalInfo["z"] = msg.z();}
            if(msg.signalId() != NULL) {signalInfo["signalId"] = msg.signalId();}
            if(msg.minValue() != NULL) {signalInfo["minValue"] = msg.minValue();}
            if(msg.maxValue() != NULL) {signalInfo["maxValue"] = msg.maxValue();}
        
            stateInfo.setActuatorInfo(actuatorInfo_json);
        };

        auto onComponentInfo = [](cluon::data::Envelope &&env){                    
            opendlv::body::ComponentInfo msg = cluon::extractMessage<opendlv::body::ComponentInfo>(std::move(env));
            json componentInfo_json;

            if(msg.description() != NULL) {signalInfo["description"] = msg.description();}
            if(msg.x() != NULL) {signalInfo["x"] = msg.x();}
            if(msg.y() != NULL) {signalInfo["y"] = msg.y();}
            if(msg.z() != NULL) {signalInfo["z"] = msg.z();}
            
            stateInfo.setComponentInfo(componentInfo_json);
        };

        auto onAccelerationReading = [](cluon::data::Envelope &&env){                    
            opendlv::proxy::AccelerationReading msg = cluon::extractMessage<opendlv::body::AccelerationReading>(std::move(env));
            json accelerationReading_json;

            if(msg.accelerationX() != NULL) {signalInfo["accelerationX"] = msg.accelerationX();}
            if(msg.accelerationY() != NULL) {signalInfo["accelerationY"] = msg.accelerationY();}
            if(msg.accelerationZ() != NULL) {signalInfo["accelerationZ"] = msg.accelerationZ();}
            
            stateInfo.setAccelerationReading(accelerationReading_json);
        };

        auto onAngularVelocityReading = [](cluon::data::Envelope &&env){                    
            opendlv::proxy::AngularVelocityReading msg = cluon::extractMessage<opendlv::proxy::AngularVelocityReading>(std::move(env));
            json angularVelocityReading_json;

            if(msg.angularVelocityX() != NULL) {signalInfo["angularVelocityX"] = msg.angularVelocityX();}
            if(msg.angularVelocityY() != NULL) {signalInfo["angularVelocityY"] = msg.angularVelocityY();}
            if(msg.angularVelocityZ() != NULL) {signalInfo["angularVelocityZ"] = msg.angularVelocityZ();}
            
            stateInfo.setAngularVelocityReading(angularVelocityReading_json);
        };

        auto onMagneticFieldReading = [](cluon::data::Envelope &&env){                    
            opendlv::proxy::MagneticFieldReading msg = cluon::extractMessage<opendlv::proxy::MagneticFieldReading>(std::move(env));
            json magneticFieldReading_json;

            if(msg.magneticFieldX() != NULL) {signalInfo["magneticFieldX"] = msg.magneticFieldX();}
            if(msg.magneticFieldY() != NULL) {signalInfo["magneticFieldY"] = msg.magneticFieldY();}
            if(msg.magneticFieldZ() != NULL) {signalInfo["magneticFieldZ"] = msg.magneticFieldZ();}
            
            stateInfo.setMagneticFieldReading(magneticFieldReading_json);
        };

        auto onAltitudeReading = [](cluon::data::Envelope &&env){                    
            opendlv::proxy::AltitudeReading msg = cluon::extractMessage<opendlv::proxy::AltitudeReading>(std::move(env));
            json altitudeReading_json;

            if(msg.altitude() != NULL) {signalInfo["altitude"] = msg.altitude();}

            stateInfo.setAltitudeReading(altitudeReading_json);
        };

        auto onPressureReading = [](cluon::data::Envelope &&env){                    
            opendlv::proxy::PressureReading msg = cluon::extractMessage<opendlv::proxy::PressureReading>(std::move(env));
            json pressureReading_json;

            if(msg.pressure() != NULL) {signalInfo["pressure"] = msg.pressure();}

            stateInfo.setPressureReading(pressureReading_json);
        };

        auto onTemperatureReading = [](cluon::data::Envelope &&env){                    
            opendlv::proxy::TemperatureReading msg = cluon::extractMessage<opendlv::proxy::TemperatureReading>(std::move(env));
            json pressureReading_json;

            if(msg.temperature() != NULL) {signalInfo["temperature"] = msg.temperature();}

            stateInfo.setTemperatureReading(temperatureReading_json);
        };

        auto onImageReadingShared = [](cluon::data::Envelope &&env){                    
            opendlv::proxy::ImageReadingShared msg = cluon::extractMessage<opendlv::proxy::ImageReadingShared>(std::move(env));
            json imageReadingShared_json;

            if(msg.name() != NULL) {signalInfo["name"] = msg.name();}
            if(msg.size() != NULL) {signalInfo["size"] = msg.size();}
            if(msg.width() != NULL) {signalInfo["width"] = msg.width();}
            if(msg.height() != NULL) {signalInfo["height"] = msg.height();}
            if(msg.bytesPerPixel() != NULL) {signalInfo["bytesPerPixel"] = msg.bytesPerPixel();}

            stateInfo.setImageReadingShared(imageReadingShared_json);
        };

        auto onPointCloudReading = [](cluon::data::Envelope &&env){                    
            opendlv::proxy::PointCloudReading msg = cluon::extractMessage<opendlv::proxy::PointCloudReading>(std::move(env));
            json pointCloudReading_json;

            if(msg.startAzimuth() != NULL) {signalInfo["startAzimuth"] = msg.startAzimuth();}
            if(msg.endAzimuth() != NULL) {signalInfo["endAzimuth"] = msg.endAzimuth();}
            if(msg.entriesPerAzimuth() != NULL) {signalInfo["entriesPerAzimuth"] = msg.entriesPerAzimuth();}
            if(msg.distances() != NULL) {signalInfo["distances"] = msg.distances();}
            if(msg.numberOfBitsForIntensity() != NULL) {signalInfo["numberOfBitsForIntensity"] = msg.numberOfBitsForIntensity();}

            stateInfo.setPointCloudReading(pointCloudReading_json);
        };

        auto onPointCloudReadingShared = [](cluon::data::Envelope &&env){                    
            opendlv::proxy::PointCloudReadingShared msg = cluon::extractMessage<opendlv::proxy::PointCloudReadingShared>(std::move(env));
            json pointCloudReadingShared_json;

            if(msg.name() != NULL) {signalInfo["name"] = msg.name();}
            if(msg.size() != NULL) {signalInfo["size"] = msg.size();}
            if(msg.width() != NULL) {signalInfo["width"] = msg.width();}
            if(msg.height() != NULL) {signalInfo["height"] = msg.height();}
            if(msg.numberOfComponentsPerPoint() != NULL) {signalInfo["numberOfComponentsPerPoint"] = msg.numberOfComponentsPerPoint();}

            stateInfo.setPointCloudReadingShared(pointCloudReadingShared_json);
        };

        auto onSignalStatusMessage = [](cluon::data::Envelope &&env){                    
            opendlv::system::SignalStatusMessage msg = cluon::extractMessage<opendlv::system::SignalStatusMessage>(std::move(env));
            json signalStatusMessage_json;

            if(msg.code() != NULL) {signalInfo["code"] = msg.code();}
            if(msg.description() != NULL) {signalInfo["description"] = msg.description();}
            
            stateInfo.setSignalStatusMessage(signalStatusMessage_json);
        };

        auto onSystemOperationState = [](cluon::data::Envelope &&env){                    
            opendlv::system::SystemOperationState msg = cluon::extractMessage<opendlv::system::SystemOperationState>(std::move(env));
            json systemOperationState_json;

            if(msg.code() != NULL) {signalInfo["code"] = msg.code();}
            if(msg.description() != NULL) {signalInfo["description"] = msg.description();}
            
            stateInfo.setSystemOperationState(systemOperationState_json);
        };

        auto onNetworkStatusMessage = [](cluon::data::Envelope &&env){                    
            opendlv::system::NetworkStatusMessage msg = cluon::extractMessage<opendlv::system::NetworkStatusMessage>(std::move(env));
            json networkStatusMessage_json;

            if(msg.code() != NULL) {signalInfo["code"] = msg.code();}
            if(msg.description() != NULL) {signalInfo["description"] = msg.description();}
            
            stateInfo.setNetworkStatusMessage(networkStatusMessage_json);
        };

        auto onGeolocation = [](cluon::data::Envelope &&env){                    
            opendlv::logic::sensation::Geolocation msg = cluon::extractMessage<opendlv::logic::sensation::Geolocation>(std::move(env));
            json geolocation_json;

            if(msg.latitude() != NULL) {
                signalInfo["latitude"] = msg.latitude();
                conning_msg["geolocation"]["lat"] = msg.latitude();                
            }
            if(msg.longitude() != NULL) {
                signalInfo["longitude"] = msg.longitude();
                conning_msg["geolocation"]["long"] = msg.longitude();
            }
            if(msg.altitude() != NULL) {
                signalInfo["altitude"] = msg.altitude();
                conning_msg["geolocation"]["alt"] = msg.altitude();
            }
            if(msg.heading() != NULL) {
                signalInfo["heading"] = msg.heading();
                conning_msg["geolocation"]["heading"] = msg.heading()
            }
            
            stateInfo.setGeolocation(geolocation_json);
        };


        // To fix --> only in conning for now
        auto onGroundSpeedReading = [](cluon::data::Envelope &&env){
            opendlv::proxy::GroundSpeedReading msg = cluon::extractMessage<opendlv::proxy::GroundSpeedReading>(std::move(env));
                conning_msg["GroundSpeedReading"]["cog"] = msg.groundSpeed();
                conning_msg["GroundSpeedReading"]["sog"] = msg.groundSpeed();
        }

    }

    // Triggers for the different messages

    od4.dataTrigger(opendlv::body::SensorInfo::ID(), onSensorInfo);
    od4.dataTrigger(opendlv::body::ComponentInfo::ID(), onComponentInfo);
    od4.dataTrigger(opendlv::body::ActuatorInfo::ID(), onActuatorInfo);
    od4.dataTrigger(opendlv::body::SignalInfo::ID(), onSignalInfo);
    od4.dataTrigger(opendlv::proxy::AccelerationReading::ID(), onAccelerationReading);
    od4.dataTrigger(opendlv::proxy::AngularVelocityReading::ID(), onAngularVelocityReading);
    od4.dataTrigger(opendlv::proxy::MagneticFieldReading::ID(), onMagneticFieldReading);
    od4.dataTrigger(opendlv::proxy::AltitudeReading::ID(), onAltitudeReading);
    od4.dataTrigger(opendlv::proxy::PressureReading::ID(), onPressureReading);
    od4.dataTrigger(opendlv::proxy::TemperatureReading::ID(), onTemperatureReading);
    od4.dataTrigger(opendlv::proxy::ImageReadingShared::ID(), onImageReadingShared);
    od4.dataTrigger(opendlv::proxy::PointCloudReading::ID(), onPointCloudReading);
    od4.dataTrigger(opendlv::proxy::PointCloudReadingShared::ID(), onPointCloudReadingShared);
    od4.dataTrigger(opendlv::system::SignalStatusMessage::ID(), onSignalStatusMessage);
    od4.dataTrigger(opendlv::system::SystemOperationState::ID(), onSystemOperationState);
    od4.dataTrigger(opendlv::system::NetworkStatusMessage::ID(), onNetworkStatusMessage);
    od4.dataTrigger(opendlv::logic::sensation::Geolocation::ID(), onGeolocation);



}
opendlv_handler::on_receive(std::string msg) {

    // I know this shouldn't be exactly like this, should I send it
    // to the requesting device? Or maybe make a list with the devices that ask for it?
    // But I don't have their urls

    std::string requested_dev;
    std::string acquired_dev;

    json json_msg = json::parse(msg);

    if (json_msg.contains("request")) {
        requested_dev = json_msg.at("request");
        if(requested_dev.compare("SensorInfo") != 0) {
            _send(stateInfo.getSensorInfo());
        } else if (requested_dev.compare("ComponentInfo") != 0) {
            _send(stateInfo.getComponentInfo());
        } else if (requested_dev.compare("ActuatorInfo") != 0) {
            _send(stateInfo.getActuatorInfo());
        } else if (requested_dev.compare("SignalInfo") != 0) {
            _send(stateInfo.getSignalInfo());
        } else if (requested_dev.compare("AccelerationReading") != 0) {
            _send(stateInfo.getAccelerationReading());
        } else if (requested_dev.compare("AngularVelocityReading") != 0) {
            _send(stateInfo.getAngularVelocityReading());
        } else if (requested_dev.compare("MagneticFieldReading") != 0) {
            _send(stateInfo.getMagneticFieldReading());
        } else if (requested_dev.compare("AltitudeReading") != 0) {
            _send(stateInfo.getAltitudeReading());
        } else if (requested_dev.compare("PressureReading") != 0) {
            _send(stateInfo.getPressureReading());
        } else if (requested_dev.compare("TemperatureReading") != 0) {
            _send(stateInfo.getTemperatureReading());
        } else if (requested_dev.compare("ImageReadingShared") != 0) {
            _send(stateInfo.getImageReadingShared());
        } else if (requested_dev.compare("PointCloudReading") != 0) {
            _send(stateInfo.getPointCloudReading());
        } else if (requested_dev.compare("PointCloudReadingShared") != 0) {
            _send(stateInfo.getPointCloudReadingShared());
        } else if (requested_dev.compare("SignalStatusMessage") != 0) {
            _send(stateInfo.getSignalStatusMessage());
        } else if (requested_dev.compare("SystemOperationState") != 0) {
            _send(stateInfo.getSystemOperationState());
        } else if (requested_dev.compare("NetworkStatusMessage") != 0) {
            _send(stateInfo.getNetworkStatusMessage());
        } else if (requested_dev.compare("Geolocation") != 0) {
            _send(stateInfo.getGeolocation());
        } else if (requested_dev.compare("conning") != 0) {
            _send(conning_msg);
        }
    }
}
} // namespace vrgp_adapter
