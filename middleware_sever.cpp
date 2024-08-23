#include "server/Server.hpp"
#include <thread>
#include <iostream>
#include <chrono>

using std::thread, std::cout;

void handle_subscriber(ip::tcp::socket socket)
{
    cout << "Invoked";

    WebSubscriber subscriber(std::move(socket));
    subscriber._test_api();
    for (;;)
    {
    };
}
void handle_publisher(ip::tcp::socket socket)
{

    ContentPublsiher publisher(std::move(socket));
    publisher.watch_and_update_notification_queue();
}

void accepting(ip::tcp::acceptor &acceptor, asio::io_context &io_context, bool &is_publisher_available)
{
    is_publisher_available = false;
    acceptor.async_accept(io_context, [&is_publisher_available](const auto &error, ip::tcp::socket socket)
                          { 
                            is_publisher_available=true;
                            cout << "Accepted";
                            handle_publisher(std::move(socket));
                            accepting(ip::tcp::acceptor acceptor, asio::io_context io_context, bool &is_publisher_available) });
}

int main()
{
    std::system("cls");

    asio::io_context io_context;
    ip::address subscriber_address = ip::make_address("127.0.0.1");
    ip::port_type subscriber_port = ip::port_type(88);
    ip::tcp::endpoint subscriber_endpoint(subscriber_address, subscriber_port);

    ip::address publisher_address = ip::make_address("127.0.0.1");
    ip::port_type publisher_port = ip::port_type(89);
    ip::tcp::endpoint publisher_endpoint(publisher_address, publisher_port);

    ip::tcp::acceptor subscriber_acceptor(io_context, subscriber_endpoint);
    ip::tcp::acceptor publisher_acceptor(io_context, publisher_endpoint);
    bool is_publisher_available = true;
    bool is_subscriber_available = true;
    ip::tcp::socket publisher_socket(io_context);

    while (true)
    {
        if (is_publisher_available)
        {
            accepting(publisher_acceptor, io_context, is_publisher_available);
        }
    }
    // while (true)
    // {
    //     if (is_publisher_available)
    //     {
    //         cout << "Came here";
    //         is_publisher_available = false;
    //     }

    // if (is_subscriber_available)
    // {
    //     is_subscriber_available = false;

    //     ip::tcp::socket subscriber_socket(io_context);
    //     subscriber_acceptor.async_accept(io_context, [&is_subscriber_available](const auto &error, ip::tcp::socket socket)
    //                                      {
    //                                         cout << "Accepted";
    //                                         is_subscriber_available=true;
    //                                         handle_subscriber(std::move(socket)); });
    // }
    // }

    io_context.run();
}