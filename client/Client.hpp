#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include <array>
#include <memory>
#include <boost/beast.hpp>

namespace asio = boost::asio;
namespace ip = asio::ip;
namespace beast = boost::beast;

using tcp = asio::ip::tcp;
using std::string, std::vector, std::array;

class Publisher
{
public:
    Publisher();
    void connect(string ip, string port);
    void disconnect();
    void push_new_message(string message);

private:
    asio::io_context io_context;
    string host;

protected:
    std::unique_ptr<beast::websocket::stream<tcp::socket>> websocket;
    void configure_websocket();
};
