
#ifndef GLOBAL_NOTIFICATION_QUEUE
#define GLOBAL_NOTIFICATION_QUEUE
#include "NotificationQueue.hpp"
#endif

#include <array>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <memory>
#include "../utils/Session.hpp"

namespace asio = boost::asio;
namespace ip = asio::ip;
namespace beast = boost::beast;
namespace http = boost::beast::http;

using std::string, std::array;
using tcp = ip::tcp;

class ServerPublisher
{

public:
    ServerPublisher(string topic, ip::tcp::socket socket_);
    void read_new_message();
    void publish_message(string message);

private:
    StockNotificationQueue *notification_queue;
    string topic;
    std::unique_ptr<beast::websocket::stream<tcp::socket>> websocket;
    void add_websocket_decorator();
};

class ServerSubscriber : public Observer
{
public:
    ServerSubscriber(string topic, ip::tcp::socket socket_);
    void update(Subject *changed_subject);
    ~ServerSubscriber();

private:
    string topic;
    std::unique_ptr<beast::websocket::stream<tcp::socket>> websocket;
    StockNotificationQueue *notification_queue;
};

struct ClientMetaData
{
    string topic;
    string type;
};
