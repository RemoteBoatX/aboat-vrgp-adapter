class state {
private:

	// No request messages

	std::string sensorInfo_json;
	std::string actuatorInfo_json;
	std::string componentInfo_json;
	std::string signalInfo_json;
	std::string accelerationReading_json;
	std::string angularVelocityReading_json;
	std::string magneticFieldReading_json;
	std::string altitudeReading_json;
	std::string pressureReading_json;
	std::string temperatureReading_json;
	std::string imageReadingShared_json;
	std::string pointCloudReading_json;
	std::string signalStatus_json;
	std::string systemOperationState_json;
	std::string networkStatus_json;
	std::string geolocation_json;
	std::string conning_json;

public:

	void setSensorInfo(std::string msg) {
		sensorInfo_json = msg;		
	}

	std::string getSensorInfo() {
		return sensorInfo_json;
	}

	void setActuatorInfo(std::string msg) {
		actuatorInfo_json = msg;		
	}

	std::string getActuatorInfo() {
		return actuatorInfo_json;
	}

	void setComponentInfo(std::string msg) {
		componentInfo_json = msg;		
	}

	std::string getComponentInfo() {
		return componentInfo_json;
	}
	
	void setSignalInfo(std::string msg) {
		signalInfo_json = msg;
	}
	
	std::string getSignalInfo() {
		return signalInfo_json;
	}

	void setAccelerationReading(std::string msg) {
		accelerationReading_json = msg;		
	}

	std::string getAccelerationReading() {
		return accelerationReading_json;
	}

	void setAngularVelocityReading(std::string msg) {
		angularVelocityReading_json = msg;		
	}

	std::string getAngularVelocityReading() {
		return angularVelocityReading_json;
	}

	void setMagneticFieldReading(std::string msg) {
		magneticFieldReading_json = msg;		
	}

	std::string getMagneticFieldReading() {
		return magneticFieldReading_json;
	}

	void setAltitudeReading(std::string msg) {
		altitudeReading_json = msg;		
	}

	std::string getAltitudeReading() {
		return altitudeReading_json;
	}

	void setPressureReading(std::string msg) {
		pressureReading_json = msg;		
	}

	std::string getPressureReading() {
		return pressureReading_json;
	}
	
	void setTemperatureReading(std::string msg) {
		temperatureReading_json = msg;		
	}

	std::string getTemperatureReading() {
		return temperatureReading_json;
	}

	void setImageReadingShared(std::string msg) {
		imageReadingShared_json = msg;		
	}

	std::string getImageReadingShared() {
		return imageReadingShared_json;
	}

	void setPointCloudReading(std::string msg) {
		pointCloudReading_json = msg;		
	}

	std::string getPointCloudReading() {
		return pointCloudReading_json;
	}

	void setSignalStatusMessage(std::string msg) {
		signalStatus_json = msg;		
	}

	std::string getSignalStatusMessage() {
		return signalStatus_json;
	}

	void setSystemOperationState(std::string msg) {
		systemOperationState_json = msg;		
	}

	std::string getSystemOperationState() {
		return systemOperationState_json;
	}

	void setNetworkStatusMessage(std::string msg) {
		networkStatus_json = msg;		
	}

	std::string getNetworkStatusMessage() {
		return networkStatus_json;
	}

	void setGeolocation(std::string msg) {
		geolocation_json = msg;		
	}

	std::string getGeolocation() {
		return geolocation_json;
	}
	
	void setConning(std::string msg) {
		conning_json = msg;		
	}

	std::string getConning() {
		return conning_json;
	}
};
