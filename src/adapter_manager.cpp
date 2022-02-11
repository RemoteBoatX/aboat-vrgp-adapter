#include "adapter_manager.hpp"

namespace vrgp_adapter {

adapter_manager::adapter_manager(std::string const & url)
        : _client_ptr(nullptr),
            _client_thread_ptr(nullptr),
            _opendlv_handler_ptr(nullptr),
            _opendlv_handler_thread_ptr(nullptr),
            _done(false) {

    // convert the member function to a normal function, that takes in an extra
    // parameter (the `this` object)
    std::function<void (vrgp_adapter::adapter_manager*, std::string)> f_ws =
        std::mem_fn(&vrgp_adapter::adapter_manager::on_receive);

    // bind the first parameter of that class to be the `this` object
    // and the second one to be a placeholder for the passed string
    auto on_receive_func = std::bind(f_ws, this, std::placeholders::_1);

    // create a websocket client instance
    _client_ptr = websocketpp::lib::make_shared<vrgp_adapter::websocket_client>(url, on_receive_func, _done);

    // convert the member function to a normal function, that takes in an extra
    // parameter (the `this` object)
    std::function<void (vrgp_adapter::adapter_manager*, std::string)> f_odv_hdl =
        std::mem_fn(&vrgp_adapter::adapter_manager::send);

    // bind the first parameter of that class to be the `this` object
    // and the second one to be a placeholder for the passed string
    auto send_func = std::bind(f_odv_hdl, this, std::placeholders::_1);

    // create an opendlv handler instance
    _opendlv_handler_ptr = websocketpp::lib::make_shared<vrgp_adapter::opendlv_handler>(send_func, _done);
}

adapter_manager::~adapter_manager() {

#ifdef BUILD_DEBUG
    assert(_client_thread_ptr != nullptr);
    assert(_opendlv_handler_thread_ptr != nullptr);
#endif

    _client_thread_ptr->join();
    _opendlv_handler_thread_ptr->join();
}

void adapter_manager::run() {

    // start the WebSocket thread
    _client_thread_ptr = websocketpp::lib::make_shared<websocketpp::lib::thread>(
        &vrgp_adapter::websocket_client::run,
        _client_ptr
    );

    _opendlv_handler_thread_ptr = websocketpp::lib::make_shared<websocketpp::lib::thread>(
        &vrgp_adapter::opendlv_handler::run,
        _opendlv_handler_ptr
    );

#ifdef BUILD_DEBUG
    assert(_client_thread_ptr != nullptr);
    assert(_opendlv_handler_thread_ptr != nullptr);
#endif

}

} // namespace vrgp_adapter
