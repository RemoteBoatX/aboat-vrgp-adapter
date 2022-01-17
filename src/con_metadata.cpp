#include "con_metadata.hpp"

/* connection_metadata::connection_metadata() { */
/* } */

void connection_metadata::on_open(client_endpoint *endpoint, websocketpp::connection_hdl handler) {
    std::cout << "Succesfully opened connection!" << std::endl;
}

void connection_metadata::on_fail(client_endpoint *endpoint, websocketpp::connection_hdl handler) {
    std::cout << "Failed connection!" << std::endl;
}

void connection_metadata::on_close(client_endpoint * endpoint, websocketpp::connection_hdl handler) {
    std::cout << "Closing connection..." << std::endl;
}

// TODO logic for receive message
void connection_metadata::on_message(websocketpp::connection_hdl handler, client_endpoint::message_ptr msg) {

    if (msg->get_opcode() == websocketpp::frame::opcode::text) {
        std::cout << "text: " << msg->get_payload() << std::endl;
    } else if (msg->get_opcode() == websocketpp::frame::opcode::binary) {
        std::cout << "binary: " << msg->get_payload() << std::endl;
    } else {
        std::cout << "Error when reading message!!\n";
    }
}
