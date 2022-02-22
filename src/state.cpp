class state {
private:

	std::string sensorInfo_json;

public:

	void setSensorInfo(std::string msg) {
		sensorInfo_json = msg;		
	}

	std::string getSensorInfo() {
		return sensorInfo_json;
	}
}