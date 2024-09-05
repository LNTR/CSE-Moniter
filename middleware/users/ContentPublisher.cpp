
#include "ContentPublisher.hpp"

ContentPublsiher::ContentPublsiher(tcp::socket socket_) : Client(std::move(socket_)) {};

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
