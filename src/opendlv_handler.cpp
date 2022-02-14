#include "opendlv_handler.hpp"

namespace vrgp_adapter {

opendlv_handler::opendlv_handler(websocketpp::lib::function<void (std::string)> send_func, std::atomic_bool& done)
    : _send(send_func),
      _done(done),

      // get the OD4 session number from the environment variables
      _od4_session_nr(std::stoi(std::string(std::getenv("OD4_SESSION")))),

      // create the OD4 session
      _od4_session(_od4_session_nr) {

}

opendlv_handler::~opendlv_handler() {
}

void opendlv_handler::run() {

    // if the od4 session is running, register method handlers for the
    // connection to the Åboat
    // (see 'connection_messages.odvd' for how the messages look like)
    if (_od4_session.isRunning()) {

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
        auto onConnectionClose = [this](cluon::data::Envelope &&env) {

            // extract the URL from the OpenDLV message
            ConnectionClose conn = cluon::extractMessage<ConnectionClose>(std::move(env));

            // construct the JSON message
            nlohmann::json jsonMsg;
            jsonMsg["close"] = conn.url();

            // send the json message to the VRGP service
            _send(jsonMsg.dump());
        };

        // register the handlers
        _od4_session.dataTrigger(ConnectionEstablish::ID(), onConnectionEstablish);
        _od4_session.dataTrigger(ConnectionClose::ID(), onConnectionClose);
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
    try {
        json = nlohmann::json::parse(msg);
    } catch (nlohmann::detail::parse_error e) {
        std::cout << "Couldn't parse JSON message, error: "
            << e.what()
            << ". Skipping message..."
            << std::endl;

        goto parse_error;
    }

    // if the json contains a close key, then send it further to the Åboat
    if (json.contains("close")) {

        if (_od4_session.isRunning()) {

            ConnectionClose conn;

            conn.url(json["close"]);

            _od4_session.send(conn);
        }
    }

parse_error:
    ;
}

} // namespace vrgp_adapter
