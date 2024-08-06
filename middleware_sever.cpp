#include "server/Server.hpp"
#include <thread>
#include <iostream>

using std::thread, std::cout;

void handle_subscriber(ip::tcp::socket socket_)
{
    WebClient subscriber(std::move(socket_));

    for (;;)
    {
    }
}

int main()
{
    std::system("cls");

    asio::io_context io_context;
    ip::address address = ip::make_address("127.0.0.1");
    ip::port_type port = ip::port_type(88);

    ip::tcp::endpoint endpoint(address, port);

    ip::tcp::acceptor acceptor(io_context, endpoint);

    ip::tcp::socket socket(io_context);

    for (;;)
    {
        acceptor.accept(socket);
        thread connection(handle_subscriber, std::move(socket));
        connection.detach();
    }
}