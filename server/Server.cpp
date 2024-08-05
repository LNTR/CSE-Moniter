#include "Server.hpp"
#include <boost/algorithm/string.hpp>

using std::string, std::move, ip::tcp;

StockNotificationQueue global_notification_queue;

ServerPublisher::ServerPublisher(string topic, tcp::socket socket_)
{
    this->topic = topic;
    this->notification_queue = &global_notification_queue;
    this->websocket = std::make_unique<beast::websocket::stream<tcp::socket>>(std::move(socket_));
    websocket->text(true);
    add_websocket_decorator();
};
void ServerPublisher::add_websocket_decorator()
{
    auto lambda = [](beast::websocket::response_type &res)
    {
        res.set(http::field::server,
                std::string(BOOST_BEAST_VERSION_STRING) +
                    " websocket-server-sync");
    };

    websocket->set_option(beast::websocket::stream_base::decorator(lambda));
}

void ServerPublisher::read_new_message()
{
    beast::flat_buffer buffer;
    websocket->read(buffer);

    if (buffer.size() > 0)
    {
        publish_message(beast::buffers_to_string(buffer));
    }
}

void ServerPublisher::publish_message(string message)
{
    Notification aspect = {topic, message};
    notification_queue->push_new_notification(aspect);
}

ServerSubscriber::ServerSubscriber(string topic, tcp::socket socket_)
{
    this->topic = topic;
    this->notification_queue = &global_notification_queue;
    this->websocket = std::make_unique<beast::websocket::stream<tcp::socket>>(std::move(socket_));
    this->notification_queue->attach(this);
    websocket->text(true);
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
