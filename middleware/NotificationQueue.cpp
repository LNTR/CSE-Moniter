#include <iostream>
#include "NotificationQueue.hpp"

StockNotificationQueue::StockNotificationQueue()
{
    notification_queue = {};
}

void StockNotificationQueue::push_new_notification(Notification notification)
{
    shared_lock.lock();
    notification_queue.push_back(notification);
    notify();
    shared_lock.unlock();
}

Notification StockNotificationQueue::pull_new_notification()
{
    Notification notification = notification_queue.back();
    return notification;
}
