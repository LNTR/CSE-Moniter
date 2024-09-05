#include "Client.hpp"
#include "NotificationQueue.hpp"
#include <boost/algorithm/string.hpp>

class ContentPublsiher : public Client
{
public:
    ContentPublsiher(ip::tcp::socket socket_);
    void watch_and_update_notification_queue();

private:
    StockNotificationQueue *notification_queue;
};
