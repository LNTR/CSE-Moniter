#include "server/Server.hpp"
#include <thread>
#include <iostream>
#include <chrono>

using std::thread, std::cout;

void handle_subscriber(ip::tcp::socket socket_)
{
    WebSubscriber subscriber(std::move(socket_));

    for (;;)
    {
        subscriber._test_api();
        cout << "Message Sent\n";
        std::this_thread::sleep_for(std::chrono::seconds(5));
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

    // for (;;)
    // {
    //     thread connection(handle_subscriber, std::move(socket));
    //     connection.detach();
    // }
    for (;;)
    {
        acceptor.accept(socket);
        handle_subscriber(std::move(socket));
    }
}