
#ifndef GLOBAL_NOTIFICATION_QUEUE
#define GLOBAL_NOTIFICATION_QUEUE
#include "NotificationQueue.hpp"
#endif

#include <array>
#include <boost/asio.hpp>

namespace asio = boost::asio;
namespace ip = asio::ip;

using std::string, std::array;
class ServerPublisher
{

public:
    ServerPublisher(string topic, ip::tcp::socket socket_);
    void read_new_message();
    void publish_message(string message);

private:
    NotificationQueue *notification_queue;
    string topic;
    ip::tcp::socket socket;
};

class ServerSubscriber : public Observer
{
public:
    ServerSubscriber(string topic, ip::tcp::socket socket_);
    void update(Subject *changed_subject);
    ~ServerSubscriber();

private:
    string topic;
    ip::tcp::socket socket;
    NotificationQueue *notification_queue;
};

struct ClientMetaData
{
    string topic;
    string type;
};

ClientMetaData get_meta_data(ip::tcp::socket &socket);