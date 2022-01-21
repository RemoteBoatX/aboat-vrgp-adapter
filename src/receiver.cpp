// Include the header-only libcluon file.
#include "cluon-complete.hpp"

// Include our self-contained message definition.
#include "mymessages.hpp"

// We will use iostream to print the received message.
#include <iostream>

// We will use chrono and thread to sleep for a while.
#include <chrono>
#include <thread>

// For writing in the json
#include <string>
#include <fstream>

int find_devices() {



    // We open a session and wait for messages to arrive
    cluon::OD4Session od4{111, [](cluon::data::Envelope &&env){
            
            std::cout << "Data type = " << env.dataType() << std::endl;
            
            // Didn't find the message of request from the Aboat to the MOC
            //TO DO -> Write device on json         
        }
    };

    // Let's wait for 10s to receive messages.
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(10s);

    return(0);
}

int main(int argc, char **argv) {

    find_devices();

    return 0;
}