#include "users/ContentPublisher.hpp"
#include "users/WebSubscriber.hpp"
#include "utils/config.hpp"
#include <thread>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <format>

using std::thread, std::cout, std::unordered_map;

void handle_subscriber(ip::tcp::socket socket)
{
    WebSubscriber subscriber(std::move(socket));
    for (;;)
    {
    };
}
void handle_publisher(ip::tcp::socket socket)
{
    ContentPublsiher publisher(std::move(socket));
    publisher.watch_and_update_notification_queue();
}

ip::tcp::acceptor create_acceptor(string host, int port_number, asio::io_context &io_context)
{
    ip::address ip_address = ip::make_address(host);
    ip::port_type port = ip::port_type(port_number);
    ip::tcp::endpoint endpoint(ip_address, port);
    ip::tcp::acceptor acceptor(io_context, endpoint);
    return std::move(acceptor);
}

int main()
{
    std::system("cls");
    asio::io_context io_context;
    ip::tcp::acceptor subscriber_acceptor = create_acceptor(HOST, SUBSCRIBER_PORT_NUMBER, io_context);
    ip::tcp::acceptor publisher_acceptor = create_acceptor(HOST, PUBLISHER_PORT_NUMBER, io_context);

    while (true)
    {
        io_context.restart();
        publisher_acceptor.async_accept(io_context, [&io_context](const auto &error, ip::tcp::socket socket)
                                        {   thread(handle_publisher, std::move(socket)).detach();
                                            io_context.stop(); });
        subscriber_acceptor.async_accept(io_context, [&io_context](const auto &error, ip::tcp::socket socket)
                                         {  thread(handle_subscriber, std::move(socket)).detach();
                                            io_context.stop(); });
        io_context.run();
    }
}