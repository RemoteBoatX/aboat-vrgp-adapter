// Include the header-only libcluon file.
#include "cluon-complete.hpp"

// Include our self-contained message definition.
#include "mymessages.hpp"

// We will use chrono and thread to sleep for a while.
#include <chrono>
#include <thread>

int main(int argc, char **argv) {
    // We create an OD4Session that allows us to send data to a UDP multicast
    // session. We are using group number 100 and hence, all applications
    // belonging to the same group can receive message sent to it.
    cluon::OD4Session od4{111};

    if (od4.isRunning()) {
        // Let's wait for 5s before start sending our message.
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(5s);

        // Let's create our message and set some values.
        opendlv::logic::perception::ObjectAngularBlob msg;
        msg.objectId(25);

        // Finally, send the message.
        od4.send(msg);
        std::cout << "I've sent the message " << msg.ID() << std::endl;
    }

    return 0;
}