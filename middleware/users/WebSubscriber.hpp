
#include "patterns/ObserverPattern.hpp"
#include "Client.hpp"
#include "NotificationQueue.hpp"

class WebSubscriber : public Observer, private Client
{
public:
    WebSubscriber(ip::tcp::socket socket_);
    void update(Subject *changed_subject);
    void _test_api();
    ~WebSubscriber();

private:
    StockNotificationQueue *notification_queue;
};