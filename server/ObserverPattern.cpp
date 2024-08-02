#ifndef OBSERVER_PATTERN
#define OBSERVER_PATTERN
#include "ObserverPattern.hpp"
#endif

void Subject::attach(Observer *observer)
{
    subscribe_lock.lock();
    _observers.insert(observer);
    subscribe_lock.unlock();
}
void Subject::detach(Observer *observer)
{
    subscribe_lock.lock();
    _observers.erase(observer);
    subscribe_lock.unlock();
}
void Subject::notify()
{
    for (Observer *observer : _observers)
    {
        observer->update(this);
    }
};

Observer::~Observer(){};