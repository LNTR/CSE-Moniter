
#include "Client.hpp"

StockNotificationQueue global_notification_queue;

Client::Client(tcp::socket socket_)
{
    this->websocket = std::make_unique<beast::websocket::stream<tcp::socket>>(std::move(socket_));
    notification_queue = &global_notification_queue;
    configure_websocket();
}

void Client::configure_websocket()
{
    websocket->text(true);
    auto decoration = [](beast::websocket::response_type &res)
    {
        res.set(http::field::server,
                std::string(BOOST_BEAST_VERSION_STRING) +
                    " websocket-server-sync");
    };
    websocket->set_option(beast::websocket::stream_base::decorator(decoration));
    websocket->accept();
}

void Client::write_to_socket(string message)
{
    asio::mutable_buffer buffer = asio::buffer(message, message.length());
    websocket->write(buffer);
}

string Client::read_from_socket()
{
    beast::flat_buffer buffer;
    websocket->read(buffer);
    string message = beast::buffers_to_string(buffer.data());
    return message;
}

Client::~Client()
{
    websocket->close(beast::websocket::close_code::normal);
};