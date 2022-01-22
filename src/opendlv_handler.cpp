#include "opendlv_handler.hpp"

namespace vrgp_adapter {

opendlv_handler::opendlv_handler(websocketpp::lib::function<void (std::string)> send_func) {
    _send = send_func;
}

opendlv_handler::~opendlv_handler() {
}

void opendlv_handler::run() {
    // TODO(joan) opendlv logic
    // should continuously loop and process any message from the boat side,
    // through opendlv
}

void opendlv_handler::on_receive(std::string msg) {
    // TODO(joan) opendlv receive logic
    // should receive a message, decode it, and act accordingly (i.e. get the
    // data from the vessel etc.)
}

} // namespace vrgp_adapter
