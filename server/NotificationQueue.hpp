#ifndef OBSERVER_PATTERN
#define OBSERVER_PATTERN
#include "ObserverPattern.hpp"
#endif
#include "../utils/Session.hpp"

#include <vector>
#include <chrono>

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
    string get_new_data();
};
