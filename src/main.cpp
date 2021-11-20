#include <iostream>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>

typedef websocketpp::client<websocketpp::config::asio_client> client;

int main() {
    std::cout << "Hello world!" << std::endl;
    return 0;
}
