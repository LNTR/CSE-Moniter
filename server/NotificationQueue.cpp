#ifndef GLOBAL_NOTIFICATION_QUEUE
#define GLOBAL_NOTIFICATION_QUEUE
#include "NotificationQueue.hpp"
#endif

NotificationQueue::NotificationQueue()
{
    notification_queue = {};
}

void NotificationQueue::push_new_notification(Notification notification)
{
    shared_lock.lock();
    notification_queue.push_back(notification);
    notify();
    shared_lock.unlock();
}

Notification NotificationQueue::pull_new_notification()
{
    Notification notification = notification_queue.back();
    return notification;
}