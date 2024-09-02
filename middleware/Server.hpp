#include "NotificationQueue.hpp"
#include <array>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <memory>
#include <iostream>

namespace asio = boost::asio;
namespace ip = asio::ip;
namespace beast = boost::beast;
namespace http = boost::beast::http;

using std::string, std::array;
using tcp = ip::tcp;

//

class ServerClient
{
public:
    ServerClient(ip::tcp::socket socket_);
    ~ServerClient();

private:
    void configure_websocket();
    std::unique_ptr<beast::websocket::stream<tcp::socket>> websocket;

protected:
    void write_to_socket(string message);
    string read_from_socket();
};

//

class WebSubscriber : public Observer, private ServerClient
{
public:
    WebSubscriber(ip::tcp::socket socket_);
    void update(Subject *changed_subject);
    void _test_api();
    ~WebSubscriber();

private:
    StockNotificationQueue *notification_queue;
};

//

class ContentPublsiher : public ServerClient
{
public:
    ContentPublsiher(ip::tcp::socket socket_);
    void watch_and_update_notification_queue();

private:
    StockNotificationQueue *notification_queue;
};
