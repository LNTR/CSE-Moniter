#include "Server.hpp"
#include <boost/algorithm/string.hpp>

using std::string, std::move, ip::tcp;

StockNotificationQueue global_notification_queue;

//

WebSubscriber::WebSubscriber(tcp::socket socket_) : ServerClient(std::move(socket_))
{
    notification_queue = &global_notification_queue;
    notification_queue->attach(this);
}

void WebSubscriber::update(Subject *changed_subject)
{
    if (notification_queue == changed_subject)
    {
        Notification new_notification = notification_queue->pull_new_notification();
        std::cout << new_notification.message;
        write_to_socket(new_notification.message);
    }
}

void WebSubscriber::_test_api()
{
    string message = "Foo bar from web client";
    write_to_socket(message);
}

WebSubscriber::~WebSubscriber()
{
    this->notification_queue->detach(this);
}

//

ContentPublsiher::ContentPublsiher(tcp::socket socket_) : ServerClient(std::move(socket_))
{
    notification_queue = &global_notification_queue;
}

void ContentPublsiher::watch_and_update_notification_queue()
{
    for (;;)
    {
        string message = read_from_socket();
        if (message.length() > 1)
        {
            Notification notification{"", message};
            notification_queue->push_new_notification(notification);
        }
    }
}

//

ServerClient::ServerClient(tcp::socket socket_)
{
    this->websocket = std::make_unique<beast::websocket::stream<tcp::socket>>(std::move(socket_));
    configure_websocket();
}

void ServerClient::configure_websocket()
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

void ServerClient::write_to_socket(string message)
{
    asio::mutable_buffer buffer = asio::buffer(message, message.length());
    websocket->write(buffer);
}

string ServerClient::read_from_socket()
{
    beast::flat_buffer buffer;
    websocket->read(buffer);
    string message = beast::buffers_to_string(buffer.data());
    return message;
}

ServerClient::~ServerClient()
{
    websocket->close(beast::websocket::close_code::normal);
};
