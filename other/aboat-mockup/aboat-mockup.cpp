#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

#include "cluon-complete.hpp"
#include "connection_messages.hpp"
#include "notification_messages.hpp"

std::string currentISO8601TimeUTC() {
    auto now = std::chrono::system_clock::now();
    auto itt = std::chrono::system_clock::to_time_t(now);
    std::ostringstream ss;
    ss << std::put_time(gmtime(&itt), "%FT%TZ");
    return ss.str();
}

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
                << "signal <rais/ackn/canc> <debug/info/caution/warning/alarm/emergency> <msg> <id> <category> <source>\n"
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

        } else if (input.substr(0,6) == "signal") {

            std::string msg;
            uint16_t uid;
            std::string category;
            std::string source;
            std::string raised;
            std::string acknowledged;
            std::string cancelled;

            if (input.substr(7,4) == "rais") {
                raised = currentISO8601TimeUTC();
            } else if (input.substr(7,4) == "ackn") {
                acknowledged = currentISO8601TimeUTC();
            } else if (input.substr(7,4) == "canc") {
                cancelled = currentISO8601TimeUTC();
            }

            if (input.substr(12,4) == "info") {

                std::stringstream ss(input.substr(17));

                ss >> msg >> uid >> category >> source;

                cluon::OD4Session od4{111};

                if (od4.isRunning()) {

                    InfoNotification notif;
                    notif
                        .msg(msg)
                        .uuid(uid)
                        .category(category)
                        .source(source);

                    if (raised != "") {
                        notif.raised(raised);
                    }
                    if (acknowledged != "") {
                        notif.acknowledged(acknowledged);
                    }
                    if (cancelled != "") {
                        notif.cancelled(cancelled);
                    }


                    od4.send(notif);

                    std::cout << "Sent info signal message" << std::endl;
                }

            } else if (input.substr(12,5) == "debug") {

                std::stringstream ss(input.substr(18));

                ss >> msg >> uid >> category >> source;

                cluon::OD4Session od4{111};

                if (od4.isRunning()) {

                    DebugNotification notif;
                    notif
                        .msg(msg)
                        .uuid(uid)
                        .category(category)
                        .source(source);

                    if (raised != "") {
                        notif.raised(raised);
                    }
                    if (acknowledged != "") {
                        notif.acknowledged(acknowledged);
                    }
                    if (cancelled != "") {
                        notif.cancelled(cancelled);
                    }


                    od4.send(notif);

                    std::cout << "Sent debug signal message" << std::endl;
                }

            } else if (input.substr(12,5) == "alarm") {

                std::stringstream ss(input.substr(18));

                ss >> msg >> uid >> category >> source;

                cluon::OD4Session od4{111};

                if (od4.isRunning()) {

                    AlarmNotification notif;
                    notif
                        .msg(msg)
                        .uuid(uid)
                        .category(category)
                        .source(source);

                    if (raised != "") {
                        notif.raised(raised);
                    }
                    if (acknowledged != "") {
                        notif.acknowledged(acknowledged);
                    }
                    if (cancelled != "") {
                        notif.cancelled(cancelled);
                    }

                    od4.send(notif);

                    std::cout << "Sent alarm signal message" << std::endl;
                }

            } else if (input.substr(12,7) == "caution") {

                std::stringstream ss(input.substr(20));

                ss >> msg >> uid >> category >> source;

                cluon::OD4Session od4{111};

                if (od4.isRunning()) {

                    CautionNotification notif;
                    notif
                        .msg(msg)
                        .uuid(uid)
                        .category(category)
                        .source(source);

                    if (raised != "") {
                        notif.raised(raised);
                    }
                    if (acknowledged != "") {
                        notif.acknowledged(acknowledged);
                    }
                    if (cancelled != "") {
                        notif.cancelled(cancelled);
                    }

                    od4.send(notif);

                    std::cout << "Sent caution signal message" << std::endl;
                }

            } else if (input.substr(12,7) == "warning") {

                std::stringstream ss(input.substr(20));

                ss >> msg >> uid >> category >> source;

                cluon::OD4Session od4{111};

                if (od4.isRunning()) {

                    WarningNotification notif;
                    notif
                        .msg(msg)
                        .uuid(uid)
                        .category(category)
                        .source(source);

                    if (raised != "") {
                        notif.raised(raised);
                    }
                    if (acknowledged != "") {
                        notif.acknowledged(acknowledged);
                    }
                    if (cancelled != "") {
                        notif.cancelled(cancelled);
                    }

                    od4.send(notif);

                    std::cout << "Sent warning signal message" << std::endl;
                }

            } else if (input.substr(12,9) == "emergency") {

                std::stringstream ss(input.substr(22));

                ss >> msg >> uid >> category >> source;

                cluon::OD4Session od4{111};

                if (od4.isRunning()) {

                    EmergencyNotification notif;
                    notif
                        .msg(msg)
                        .uuid(uid)
                        .category(category)
                        .source(source);

                    if (raised != "") {
                        notif.raised(raised);
                    }
                    if (acknowledged != "") {
                        notif.acknowledged(acknowledged);
                    }
                    if (cancelled != "") {
                        notif.cancelled(cancelled);
                    }

                    od4.send(notif);

                    std::cout << "Sent emergency signal message" << std::endl;
                }

            }

        } else {
            std::cout << "> Unrecognized Command" << std::endl;
        }
    }
}
