#include "opendlv_handler.hpp"

namespace vrgp_adapter {

opendlv_handler::opendlv_handler(websocketpp::lib::function<void (std::string)> send_func, std::atomic_bool& done)
    : _send(send_func), _done(done) {
    // get the OD4 session number from the environment variables
    _od4_session = std::stoi(std::string(std::getenv("OD4_SESSION")));
}

opendlv_handler::~opendlv_handler() {
}

void opendlv_handler::run() {
    cluon::OD4Session od4{_od4_session};

    // if the od4 session is running, register method handlers for the
    // connection to the Åboat
    // (see 'connection_messages.odvd' for how the messages look like)
    if (od4.isRunning()) {

        // runs on connection establishment
        auto onConnectionEstablish = [this](cluon::data::Envelope &&env) {

            // extract the URL from the OpenDLV message
            ConnectionEstablish conn = cluon::extractMessage<ConnectionEstablish>(std::move(env));

            // construct the JSON message
            nlohmann::json jsonMsg;
            jsonMsg["connect"] = conn.url();

            // send the json message to the VRGP service
            _send(jsonMsg.dump());
        };

        // runs on connection closure
        auto onConnectionClosure = [this](cluon::data::Envelope &&env) {

            // extract the URL from the OpenDLV message
            ConnectionClose conn = cluon::extractMessage<ConnectionClose>(std::move(env));

            // construct the JSON message
            nlohmann::json jsonMsg;
            jsonMsg["close"] = conn.url();

            // send the json message to the VRGP service
            _send(jsonMsg.dump());
        };

        // register the handlers
        od4.dataTrigger(ConnectionEstablish::ID(), onConnectionEstablish);
        od4.dataTrigger(ConnectionClose::ID(), onConnectionEstablish);
    }

    // keep the event loop running, in order for the opendlv message
    // handler to run
    while(!_done) {
    }
}

void opendlv_handler::on_receive(std::string msg) {
    // TODO(joan) opendlv receive logic
    // should receive a message, decode it, and act accordingly (i.e. get the
    // data from the vessel etc.)

    // create a json object
    nlohmann::json json;

    // parse the json from the message received from the VRGP service
    json.parse(msg);

    // if the json contains a close key, then send it further to the Åboat
    if (json.contains("close")) {

        cluon::OD4Session od4{_od4_session};

        if (od4.isRunning()) {

            ConnectionClose conn;

            conn.url(json["close"]);

            od4.send(conn);
        }
    }
}

} // namespace vrgp_adapter
