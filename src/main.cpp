#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>

#include "endpoint_wrapper.hpp"


std::string get_vrgp_url() {
    // get the ip of the vrgp service
    std::string vrgp_ip = std::string(std::getenv("VRGP_IP_ADDRESS"));

    // get the port of the vrgp service
    std::string vrgp_port = std::string(std::getenv("VRGP_IP_PORT"));

    // get the path of the connection
    std::string vrgp_path = std::string(std::getenv("VRGP_IP_PATH"));

    std::string uri = "ws://" + vrgp_ip + ":" + vrgp_port + vrgp_path;

    return uri;
}

int main() {
    // get the vrgp url
    std::string url = get_vrgp_url();

    // create a client endpoint
    websocket_endpoint_wrapper client(url);

    // TODO other logic of the program here
    // send a message with `client.send(std::string)`.
}
