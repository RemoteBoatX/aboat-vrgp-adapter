#include "con_metadata.hpp"

connection_metadata::connection_metadata(int id, websocketpp::connection_hdl handler, std::string uri)
    : _id(id)
    , _handler(handler)
    , _status("Connecting")
    , _uri(uri)
    , _server("N/A") {

}

void connection_metadata::on_open(configured_endpoint *endpoint, websocketpp::connection_hdl handler) {
    _status = "Open";

    configured_endpoint::connection_ptr con = endpoint->get_con_from_hdl(handler);

    _server = con->get_response_header("Server");
}

void connection_metadata::on_fail(configured_endpoint *endpoint, websocketpp::connection_hdl handler) {
    _status = "Failed";

    configured_endpoint::connection_ptr con = endpoint->get_con_from_hdl(handler);
    _server = con->get_response_header("Server");

    _error_reason = con->get_ec().message();
}

std::ostream & operator<< (std::ostream & out, connection_metadata const & data) {
    out << "> URI: " << data._uri << "\n"
        << "> Status: " << data._status << "\n"
        << "> Remote Server: " << (data._server.empty() ? "None Specified" : data._server) << "\n"
        << "> Error/close reason: " << (data._error_reason.empty() ? "N/A" : data._error_reason);

    return out;
}
