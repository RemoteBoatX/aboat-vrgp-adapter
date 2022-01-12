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

void connection_metadata::on_close(configured_endpoint * endpoint, websocketpp::connection_hdl handler) {
    _status = "Closed";

    configured_endpoint::connection_ptr con = endpoint->get_con_from_hdl(handler);
    std::stringstream s;

    s << "Close code: " << con->get_remote_close_code()
        << " (" << websocketpp::close::status::get_string(con->get_remote_close_code())
        << "), close readon: " << con->get_remote_close_reason();

    _error_reason = s.str();
}

void connection_metadata::on_message(websocketpp::connection_hdl handler, configured_endpoint::message_ptr msg) {
    if (msg->get_opcode() == websocketpp::frame::opcode::text) {
        std::cout << "text\n";
        _messages.push_back("<< " + msg->get_payload());
    } else if (msg->get_opcode() == websocketpp::frame::opcode::binary) {
        std::cout << "binary\n";
        _messages.push_back("<< " + websocketpp::utility::to_hex(msg->get_payload()));
    } else {
        std::cout << "Error when reading message!!\n";
    }
}

void connection_metadata::record_sent_message(std::string message) {
    _messages.push_back(">> " + message);
}

std::ostream & operator<< (std::ostream & out, connection_metadata const & data) {
    out << "> URI: " << data._uri << "\n"
        << "> Status: " << data._status << "\n"
        << "> Remote Server: " << (data._server.empty() ? "None Specified" : data._server) << "\n"
        << "> Error/close reason: " << (data._error_reason.empty() ? "N/A" : data._error_reason) << "\n"
        << "> Messages:\n";

    std::vector<std::string>::const_iterator it;
    for (it = data._messages.begin(); it != data._messages.end(); ++it) {
        out << "\t" << *it << "\n";
    }

    return out;
}
