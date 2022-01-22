#include <iostream>
#include <cstdlib>

#include "adapter_manager.hpp"


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
    // get the vrgp service url
    std::string url = get_vrgp_url();

    try {

        // create an adapter manager, pass in the url of the VRGP service
        vrgp_adapter::adapter_manager manager(url);

        // start the manager
        manager.run();

    } catch(websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    }
}
