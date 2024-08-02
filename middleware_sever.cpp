#include "server/Server.hpp"
#include <thread>
#include <iostream>

using std::thread, std::cout;

void handle_publisher(ip::tcp::socket socket_, string topic)
{
    ServerPublisher publisher(topic, std::move(socket_));
    for (;;)
    {
        publisher.read_new_message();
    }
}

void handle_subscriber(ip::tcp::socket socket_, string topic)
{
    ServerSubscriber subscriber(topic, std::move(socket_));

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
        ClientMetaData meta_data = get_meta_data(socket);
        if (meta_data.type == "1")
        {
            thread connection(handle_publisher, std::move(socket), meta_data.topic);
            connection.detach();
        }
        else
        {
            thread connection(handle_subscriber, std::move(socket), meta_data.topic);
            connection.detach();
        }
    }
}