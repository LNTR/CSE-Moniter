#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include <array>
#include <boost/asio.hpp>

namespace asio = boost::asio;
namespace ip = asio::ip;

using std::string, std::vector, std::array;

class Client
{
public:
    Client(string topic, int type);
    void connect(string ip, string port);
    void disconnect();

private:
    asio::io_context io_context;
    string topic;
    int type;
    void initialize_client();

protected:
    ip::tcp::socket socket;
};

class ClientPublisher : public Client
{
public:
    ClientPublisher(string topic);
    void push_new_message(string message);
};

class ClientSubscriber : public Client
{
public:
    ClientSubscriber(string topic);

    string pull_new_message();
};