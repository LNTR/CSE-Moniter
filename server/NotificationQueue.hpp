#ifndef OBSERVER_PATTERN
#define OBSERVER_PATTERN
#include "ObserverPattern.hpp"
#endif

#include <vector>

using std::string, std::vector;

struct Notification
{
    string topic;
    string message;
};

class NotificationQueue : public Subject
{

public:
    NotificationQueue();
    void push_new_notification(Notification);
    Notification pull_new_notification();

private:
    vector<Notification> notification_queue;
};
