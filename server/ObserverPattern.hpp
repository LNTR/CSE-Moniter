
#include <unordered_set>
#include <mutex>
#include <string>

using std::unordered_set, std::mutex, std::string;

class Subject;
class Observer
{
public:
    virtual void update(Subject *changed_subject) = 0;
    virtual ~Observer();
};

class Subject
{

public:
    virtual void attach(Observer *);
    virtual void detach(Observer *);
    virtual void notify();

protected:
    mutex shared_lock;
    mutex subscribe_lock;

private:
    unordered_set<Observer *> _observers;
};
