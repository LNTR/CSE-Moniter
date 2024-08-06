#include "Server.hpp"
#include <boost/algorithm/string.hpp>

using std::string, std::move, ip::tcp;

StockNotificationQueue global_notification_queue;

ServerSubscriber::ServerSubscriber(string topic, tcp::socket socket_)
{
    this->topic = topic;
    this->notification_queue = &global_notification_queue;
    this->notification_queue->attach(this);
    this->websocket = std::make_unique<beast::websocket::stream<tcp::socket>>(std::move(socket_));
    configure_websocket();
}

void ServerSubscriber::configure_websocket()
{
    websocket->text(true);
    auto lambda = [](beast::websocket::response_type &res)
    {
        res.set(http::field::server,
                std::string(BOOST_BEAST_VERSION_STRING) +
                    " websocket-server-sync");
    };
    websocket->set_option(beast::websocket::stream_base::decorator(lambda));
}

ServerSubscriber::~ServerSubscriber()
{
    this->notification_queue->detach(this);
}

void ServerSubscriber::update(Subject *changed_subject)
{
    if (notification_queue == changed_subject)
    {
        boost::system::error_code error_code;

        Notification new_notification = notification_queue->pull_new_notification();

        if (new_notification.topic == topic)
        {
            asio::mutable_buffer buffer = asio::buffer(new_notification.message, new_notification.message.length());
            websocket->write(buffer);
        }
    }
}
