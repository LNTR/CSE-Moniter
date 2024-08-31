#include "Publisher.hpp"

using std::string, std::move, ip::tcp;

Publisher::Publisher() : io_context()
{
    this->websocket = std::make_unique<beast::websocket::stream<tcp::socket>>(io_context);
}

void Publisher::connect(string ip_, string port_)
{
    ip::address address = ip::make_address(ip_);
    int port = std::stoi(port_);
    tcp::endpoint endpoint(address, port);
    tcp::socket &socket = beast::get_lowest_layer(*websocket);
    socket.connect(endpoint);
    host = ip_ + ":" + port_;
    configure_websocket();
}

void Publisher::configure_websocket()
{
    websocket->text(true);

    auto decoration = [](beast::websocket::request_type &req)
    {
        req.set(beast::http::field::user_agent,
                std::string(BOOST_BEAST_VERSION_STRING) +
                    " websocket-client-coro");
    };

    websocket->set_option(beast::websocket::stream_base::decorator(decoration));
    websocket->handshake(host, "/");
}

void Publisher::disconnect()
{
    websocket->close(beast::websocket::close_code::normal);
}

void Publisher::push_new_message(string message)
{
    asio::mutable_buffer buffer = asio::buffer(message, message.length());
    websocket->write(buffer);
}