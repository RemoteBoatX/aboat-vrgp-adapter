#include <iostream>
#include <websocketpp/client.hpp>

#include "endpoint_wrapper.hpp"


/**
 * The main loop of the program.
 *
 */
void main_loop() {
    bool done = false;
    std::string input;
    websocket_endpoint_wrapper endpoint_wrapper;

    while (!done) {
        std::cout << "Enter Command: ";
        std::getline(std::cin, input);

        if (input == "quit") {
            done = true;
        } else if (input == "help") {
            std::cout
                << "\nCommand List:\n"
                << "connect <ws uri>\n"
                << "show <connection id>\n"
                << "send <connection id> <message>\n"
                << "close <connection id> <status code> <close reason>\n"
                << "help: Display this help text\n"
                << "quit: Exit the program\n"
                << std::endl;
        } else if (input.substr(0,7) == "connect") {
            int id = endpoint_wrapper.connect(input.substr(8));
            if (id != -1) {
                std::cout << "> Created connection with id " << id << std::endl;
            }
        } else if (input.substr(0,4) == "show") {
            int id = atoi(input.substr(5).c_str());

            connection_metadata::ptr metadata = endpoint_wrapper.get_metadata(id);
            if (metadata) {
                std::cout << *metadata << std::endl;
            } else {
                std::cout << "> Unknown connection id " << id << std::endl;
            }
        } else if (input.substr(0,4) == "send") {
            std::stringstream ss(input);

            std::string cmd;
            int id;
            std::string message = "";

            ss >> cmd >> id;
            std::getline(ss, message);

            endpoint_wrapper.send(id, message);
        } else if (input.substr(0,5) == "close") {
            std::stringstream ss(input);

            std::string cmd;
            int id;
            int close_code = websocketpp::close::status::normal;
            std::string reason;

            ss >> cmd >> id >> close_code;
            std::getline(ss, reason);

            endpoint_wrapper.close(id, close_code, reason);
        } else {
            std::cout << "> Unrecognized Command" << std::endl;
        }
    }
}

int main() {
    main_loop();

    return 0;
}
