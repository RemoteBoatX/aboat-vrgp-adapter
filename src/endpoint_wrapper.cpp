#include "endpoint_wrapper.hpp"

websocket_endpoint_wrapper::websocket_endpoint_wrapper()
    : _next_id(0) {

    // clear access and logging channels, set logging behaviour to silent
    _endpoint.clear_access_channels(websocketpp::log::alevel::all);
    _endpoint.clear_error_channels(websocketpp::log::elevel::all);

    // initialize the underlying transport system
    _endpoint.init_asio();
    _endpoint.start_perpetual();

    // init a thread to run in the background to take care of connections
    _thread.reset(new websocketpp::lib::thread(&configured_endpoint::run, &_endpoint));
}

int websocket_endpoint_wrapper::connect(std::string const & uri) {

    websocketpp::lib::error_code ec;

    // acquire a connection ptr, in order to configure the connection
    configured_endpoint::connection_ptr con = _endpoint.get_connection(uri, ec);

    if (ec) {
        std::cout << "> Connection initialization error: " << ec.message() << std::endl;
        return -1;
    }

    int new_id = _next_id++;
    connection_metadata::ptr metadata_ptr(new connection_metadata(new_id, con->get_handle(), uri));
    _connection_list[new_id] = metadata_ptr;

    // run on open connection
    con->set_open_handler(websocketpp::lib::bind(
        &connection_metadata::on_open,
        metadata_ptr,
        &_endpoint,
        websocketpp::lib::placeholders::_1
    ));

    // run on failed connection
    con->set_fail_handler(websocketpp::lib::bind(
        &connection_metadata::on_fail,
        metadata_ptr,
        &_endpoint,
        websocketpp::lib::placeholders::_1
    ));

    // in the end, open the connection
    _endpoint.connect(con);

    return new_id;
}

connection_metadata::ptr websocket_endpoint_wrapper::get_metadata(int id) const {

    con_list::const_iterator metadata_it = _connection_list.find(id);
    if (metadata_it == _connection_list.end()) {
        return connection_metadata::ptr();
    } else {
        return metadata_it->second;
    }
}
