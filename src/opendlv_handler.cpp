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
            std::string url = conn.url();

            // print the url
            // TODO(alexghergh): send the JSON url to the VRGP service
            std::cout << "Requested MOC url: " << url << std::endl;
        };

        od4.dataTrigger(ConnectionEstablish::ID(), onConnectionEstablish);
    }

    // keep the event running, in order for the opendlv message handler
    // to run
    while(!_done) {
    }
}

void opendlv_handler::on_receive(std::string msg) {
    // TODO(joan) opendlv receive logic
    // should receive a message, decode it, and act accordingly (i.e. get the
    // data from the vessel etc.)
}

} // namespace vrgp_adapter
