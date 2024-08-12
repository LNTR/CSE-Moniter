#include "server/Server.hpp"
#include <thread>
#include <iostream>
#include <chrono>

using std::thread, std::cout;

void accept_subscribers()
{
    asio::io_context io_context;
    ip::address address = ip::make_address("127.0.0.1");
    ip::port_type port = ip::port_type(88);
    ip::tcp::endpoint endpoint(address, port);
    ip::tcp::acceptor acceptor(io_context, endpoint);
    ip::tcp::socket socket(io_context);

    acceptor.accept(socket);
    WebSubscriber subscriber(std::move(socket));
    for (;;)
    {
    }
}
void accept_publishers()
{
    asio::io_context io_context;
    ip::address address = ip::make_address("127.0.0.1");
    ip::port_type port = ip::port_type(89);
    ip::tcp::endpoint endpoint(address, port);
    ip::tcp::acceptor acceptor(io_context, endpoint);
    ip::tcp::socket socket(io_context);

    for (;;)
    {
        acceptor.accept(socket);
        ContentPublsiher publisher(std::move(socket));
        publisher.watch_and_update_notification_queue();
    }
}

int main()
{
    std::system("cls");

    thread subscriber_acceptor_thread(accept_subscribers);
    subscriber_acceptor_thread.detach();
    thread publisher_acceptor_thread(accept_publishers);
    publisher_acceptor_thread.detach();

    for (;;)
    {
    };
}