
#ifndef GLOBAL_NOTIFICATION_QUEUE
#define GLOBAL_NOTIFICATION_QUEUE
#include <vector>
#include <chrono>
#include "patterns/ObserverPattern.hpp"
using std::string, std::vector;

struct Notification
{
    string topic;
    string message;
};

class StockNotificationQueue : public Subject
{

public:
    StockNotificationQueue();
    void push_new_notification(Notification);
    Notification pull_new_notification();

private:
    vector<Notification> notification_queue;
};
#endif
