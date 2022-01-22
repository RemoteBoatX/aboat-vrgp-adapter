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
#include <nlohmann/json.hpp>
#include <string>
using json = nlohmann::json;         


int find_devices() {
    
    json devices_array;
    
    // We open a session and wait for messages to arrive
    // Didn't find the message of request from the Aboat to the MOC                        
    cluon::OD4Session od4{111, [&devices_array](cluon::data::Envelope &&env){                
            
            //TO DO Change to device name if possible
            std::string device_id = std::to_string(env.dataType());
            devices_array["ID_" + device_id] = env.dataType();     
            
            //Writing on the json file
            std::ofstream o("devices.json");
            o << std::setw(4) << devices_array << std::endl;                
        }
    };

    // Let's wait for 10s to receive messages.
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(15s);

    return(0);
}

int main(int argc, char **argv) {

    find_devices();

    return 0;
}