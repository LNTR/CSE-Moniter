#ifndef CLIENT
#define CLIENT
#include "NotificationQueue.hpp"

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <memory>
#include <iostream>

namespace asio = boost::asio;
namespace ip = asio::ip;
namespace beast = boost::beast;
namespace http = beast::http;

using tcp = ip::tcp;

using std::string;

class Client
{
public:
    Client(ip::tcp::socket socket_);
    StockNotificationQueue *notification_queue;

    ~Client();

private:
    void configure_websocket();
    std::unique_ptr<beast::websocket::stream<tcp::socket>> websocket;

protected:
    void write_to_socket(string message);
    string read_from_socket();
};
#endif