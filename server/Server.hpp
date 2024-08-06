
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

class WebClient : public Observer
{
public:
    WebClient(ip::tcp::socket socket_);
    void update(Subject *changed_subject);
    ~WebClient();

private:
    StockNotificationQueue *notification_queue;
    std::unique_ptr<beast::websocket::stream<tcp::socket>> websocket;
    void configure_websocket();
};
