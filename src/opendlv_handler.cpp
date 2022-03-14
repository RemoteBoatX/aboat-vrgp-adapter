#include "opendlv_handler.hpp"

namespace vrgp_adapter {

state stateInfo;
state conning;

opendlv_handler::opendlv_handler(websocketpp::lib::function<void (std::string)> send_func) {
    _send = send_func;
}

opendlv_handler::~opendlv_handler() {
}

void opendlv_handler::run() {

    json conning_msg;	
	
    // We set specific setup for every different odvd message
    cluon::OD4Session od4{150};

    if(od4.isRunning()) {
    
        auto onSensorInfo = [](cluon::data::Envelope &&env){                    
            opendlv::body::SensorInfo msg = cluon::extractMessage<opendlv::body::SensorInfo>(std::move(env));
            json sensorInfo_json;        

            sensorInfo_json["description"] = msg.description();
            sensorInfo_json["x"] = msg.x();
            sensorInfo_json["y"] = msg.y();
            sensorInfo_json["z"] = msg.z();
            sensorInfo_json["signalId"] = msg.signalId();
            sensorInfo_json["accuracyStd"] = msg.accuracyStd();
            sensorInfo_json["minFrequency"] = msg.minFrequency();
        
            stateInfo.setSensorInfo(sensorInfo_json);
        }; 
        
        auto onSignalInfo = [](cluon::data::Envelope &&env){                    
            opendlv::body::ActuatorInfo msg = cluon::extractMessage<opendlv::body::ActuatorInfo>(std::move(env));
            json signalInfo;

            signalInfo["description"] = msg.description();
            signalInfo["x"] = msg.x();
            signalInfo["y"] = msg.y();
            signalInfo["z"] = msg.z();
            signalInfo["signalId"] = msg.signalId();
            signalInfo["minValue"] = msg.minValue();
            signalInfo["maxValue"] = msg.maxValue();
        
            stateInfo.setSignalInfo(signalInfo);
        };
        
        auto onComponentInfo = [](cluon::data::Envelope &&env){                    
            opendlv::body::ComponentInfo msg = cluon::extractMessage<opendlv::body::ComponentInfo>(std::move(env));
            json componentInfo;

            componentInfo["description"] = msg.description();
            componentInfo["x"] = msg.x();
            componentInfo["y"] = msg.y();
            componentInfo["z"] = msg.z();
            
            stateInfo.setComponentInfo(componentInfo);
        };
        
        auto onAccelerationReading = [](cluon::data::Envelope &&env){                    
            opendlv::proxy::AccelerationReading msg = cluon::extractMessage<opendlv::proxy::AccelerationReading>(std::move(env));
            json accelerationReading;

            accelerationReading["accelerationX"] = msg.accelerationX();
            accelerationReading["accelerationY"] = msg.accelerationY();
            accelerationReading["accelerationZ"] = msg.accelerationZ();
            
            stateInfo.setAccelerationReading(accelerationReading);
        };
        
        auto onAngularVelocityReading = [](cluon::data::Envelope &&env){                    
            opendlv::proxy::AngularVelocityReading msg = cluon::extractMessage<opendlv::proxy::AngularVelocityReading>(std::move(env));
            json angularVelocityReading;

            angularVelocityReading["angularVelocityX"] = msg.angularVelocityX();
            angularVelocityReading["angularVelocityY"] = msg.angularVelocityY();
            angularVelocityReading["angularVelocityZ"] = msg.angularVelocityZ();
            
            stateInfo.setAngularVelocityReading(angularVelocityReading);
        };
        
        auto onMagneticFieldReading = [](cluon::data::Envelope &&env){                    
            opendlv::proxy::MagneticFieldReading msg = cluon::extractMessage<opendlv::proxy::MagneticFieldReading>(std::move(env));
            json magneticFieldReading;

            magneticFieldReading["magneticFieldX"] = msg.magneticFieldX();
            magneticFieldReading["magneticFieldY"] = msg.magneticFieldY();
            magneticFieldReading["magneticFieldZ"] = msg.magneticFieldZ();
            
            stateInfo.setMagneticFieldReading(magneticFieldReading);
        };

        auto onAltitudeReading = [](cluon::data::Envelope &&env){                    
            opendlv::proxy::AltitudeReading msg = cluon::extractMessage<opendlv::proxy::AltitudeReading>(std::move(env));
            json altitudeReading;

            altitudeReading["altitude"] = msg.altitude();

            stateInfo.setAltitudeReading(altitudeReading);
        };

        auto onPressureReading = [](cluon::data::Envelope &&env){                    
            opendlv::proxy::PressureReading msg = cluon::extractMessage<opendlv::proxy::PressureReading>(std::move(env));
            json pressureReading;

            pressureReading["pressure"] = msg.pressure();

            stateInfo.setPressureReading(pressureReading);
        };

        auto onTemperatureReading = [](cluon::data::Envelope &&env){                    
            opendlv::proxy::TemperatureReading msg = cluon::extractMessage<opendlv::proxy::TemperatureReading>(std::move(env));
            json temperatureReading;

            temperatureReading["temperature"] = msg.temperature();

            stateInfo.setTemperatureReading(temperatureReading);
        };

        auto onImageReadingShared = [](cluon::data::Envelope &&env){                    
            opendlv::proxy::ImageReadingShared msg = cluon::extractMessage<opendlv::proxy::ImageReadingShared>(std::move(env));
            json imageReadingShared;

            imageReadingShared["name"] = msg.name();
            imageReadingShared["size"] = msg.size();
            imageReadingShared["width"] = msg.width();
            imageReadingShared["height"] = msg.height();
            imageReadingShared["bytesPerPixel"] = msg.bytesPerPixel();

            stateInfo.setImageReadingShared(imageReadingShared);
        };

        auto onPointCloudReading = [](cluon::data::Envelope &&env){                    
            opendlv::proxy::PointCloudReading msg = cluon::extractMessage<opendlv::proxy::PointCloudReading>(std::move(env));
            json pointCloudReading;

            pointCloudReading["startAzimuth"] = msg.startAzimuth();
            pointCloudReading["endAzimuth"] = msg.endAzimuth();
            pointCloudReading["entriesPerAzimuth"] = msg.entriesPerAzimuth();
            pointCloudReading["distances"] = msg.distances();
            pointCloudReading["numberOfBitsForIntensity"] = msg.numberOfBitsForIntensity();

            stateInfo.setPointCloudReading(pointCloudReading);
        };

        auto onSignalStatusMessage = [](cluon::data::Envelope &&env){                    
            opendlv::system::SignalStatusMessage msg = cluon::extractMessage<opendlv::system::SignalStatusMessage>(std::move(env));
            json signalStatusMessage;

            signalStatusMessage["code"] = msg.code();
            signalStatusMessage["description"] = msg.description();
            
            stateInfo.setSignalStatusMessage(signalStatusMessage);
        };

        auto onSystemOperationState = [](cluon::data::Envelope &&env){                    
            opendlv::system::SystemOperationState msg = cluon::extractMessage<opendlv::system::SystemOperationState>(std::move(env));
            json systemOperationState;

            systemOperationState["code"] = msg.code();
            systemOperationState["description"] = msg.description();
            
            stateInfo.setSystemOperationState(systemOperationState);
        };

        auto onNetworkStatusMessage = [](cluon::data::Envelope &&env){                    
            opendlv::system::NetworkStatusMessage msg = cluon::extractMessage<opendlv::system::NetworkStatusMessage>(std::move(env));
            json networkStatusMessage;

            networkStatusMessage["code"] = msg.code();
            networkStatusMessage["description"] = msg.description();
            
            stateInfo.setNetworkStatusMessage(networkStatusMessage);
        };

        auto onGeolocation = [conning_msg](cluon::data::Envelope &&env) mutable {                    
            opendlv::logic::sensation::Geolocation msg = cluon::extractMessage<opendlv::logic::sensation::Geolocation>(std::move(env));
		json geolocation;

                geolocation["latitude"] = msg.latitude();
                conning_msg["geolocation"]["lat"] = msg.latitude();                               
                geolocation["longitude"] = msg.longitude();
                conning_msg["geolocation"]["long"] = msg.longitude();
                geolocation["altitude"] = msg.altitude();
                conning_msg["geolocation"]["alt"] = msg.altitude();
                geolocation["heading"] = msg.heading();
                conning_msg["geolocation"]["heading"] = msg.heading();
            
            	stateInfo.setGeolocation(geolocation);
            	conning.setConning(conning_msg);
        };

        // To fix --> only in conning for now
        auto onGroundSpeedReading = [conning_msg](cluon::data::Envelope &&env) mutable {
            opendlv::proxy::GroundSpeedReading msg = cluon::extractMessage<opendlv::proxy::GroundSpeedReading>(std::move(env));
                
                conning_msg["GroundSpeedReading"]["cog"] = msg.groundSpeed();
                conning_msg["GroundSpeedReading"]["sog"] = msg.groundSpeed();
                
                conning.setConning(conning_msg);
        };
        
        // Triggers for the different messages
    	od4.dataTrigger(opendlv::body::SensorInfo::ID(), onSensorInfo);  
	od4.dataTrigger(opendlv::body::SignalInfo::ID(), onSignalInfo); 
	od4.dataTrigger(opendlv::body::ComponentInfo::ID(), onComponentInfo);
	od4.dataTrigger(opendlv::proxy::AccelerationReading::ID(), onAccelerationReading); 
	od4.dataTrigger(opendlv::proxy::AngularVelocityReading::ID(), onAngularVelocityReading);  
	od4.dataTrigger(opendlv::proxy::MagneticFieldReading::ID(), onMagneticFieldReading);
	od4.dataTrigger(opendlv::proxy::AltitudeReading::ID(), onAltitudeReading);
	od4.dataTrigger(opendlv::proxy::PressureReading::ID(), onPressureReading);
	od4.dataTrigger(opendlv::proxy::TemperatureReading::ID(), onTemperatureReading);
	od4.dataTrigger(opendlv::proxy::ImageReadingShared::ID(), onImageReadingShared);
	od4.dataTrigger(opendlv::proxy::PointCloudReading::ID(), onPointCloudReading);
	od4.dataTrigger(opendlv::proxy::PointCloudReading::ID(), onPointCloudReading);
	od4.dataTrigger(opendlv::system::SignalStatusMessage::ID(), onSignalStatusMessage);
	od4.dataTrigger(opendlv::system::SystemOperationState::ID(), onSystemOperationState);
	od4.dataTrigger(opendlv::system::NetworkStatusMessage::ID(), onNetworkStatusMessage);
	od4.dataTrigger(opendlv::logic::sensation::Geolocation::ID(), onGeolocation);
    } //OD4
    
} // run function

void opendlv_handler::on_receive(std::string msg) {

    std::string requested_dev;

    json json_msg = json::parse(msg);

    if (json_msg.contains("request")) {
        requested_dev = json_msg.at("request");
        if(requested_dev.compare("SensorInfo") != 0) {
            _send(stateInfo.getSensorInfo());
        } else if (requested_dev.compare("SignalInfo") != 0) {
            _send(stateInfo.getSignalInfo());
        } else if (requested_dev.compare("ComponentInfo") != 0) {
            _send(stateInfo.getComponentInfo());
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
            _send(stateInfo.getPointCloudReading());
        } else if (requested_dev.compare("SignalStatusMessage") != 0) {
            _send(stateInfo.getSignalStatusMessage());
        } else if (requested_dev.compare("SystemOperationState") != 0) {
            _send(stateInfo.getSystemOperationState());
        } else if (requested_dev.compare("NetworkStatusMessage") != 0) {
            _send(stateInfo.getNetworkStatusMessage());
        } else if (requested_dev.compare("Geolocation") != 0) {
            _send(stateInfo.getGeolocation());
        }
    }
} // on_receive function
} // namespace vrgp_adapter
