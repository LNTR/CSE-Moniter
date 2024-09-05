#include "WebSubscriber.hpp"

WebSubscriber::WebSubscriber(tcp::socket socket_) : Client(std::move(socket_))
{
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
