#include <iostream>

#include "cluon-complete.hpp"
#include "connection_messages.hpp"

int main() {

    bool done = false;
    std::string input;

    while (!done) {
        std::cout << "Enter Command: ";
        std::getline(std::cin, input);

        if (input == "quit") {
            done = true;
        } else if (input == "help") {
            std::cout
                << "\nCommand List:\n"
                << "connect <moc url>\n"
                << "disconnect <moc url>\n"
                << "help: Display this help text\n"
                << "quit: Exit the program\n"
                << std::endl;
        } else if (input.substr(0,7) == "connect") {

            cluon::OD4Session od4{111};

            if (od4.isRunning()) {

                ConnectionEstablish conn;
                conn.url(input.substr(8));

                od4.send(conn);

                std::cout << "Sent connect message with url: " << conn.url() << std::endl;
            }

        } else if (input.substr(0,10) == "disconnect") {

            cluon::OD4Session od4{111};

            if (od4.isRunning()) {

                ConnectionClose conn;
                conn.url(input.substr(11));

                od4.send(conn);

                std::cout << "Sent disconnect message with url: " << conn.url() << std::endl;
            }

        } else {
            std::cout << "> Unrecognized Command" << std::endl;
        }
    }
}
