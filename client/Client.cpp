#include "Client.hpp"
#include <iostream>

Client::Client(string topic, int type) : io_context(), socket(io_context)
{
    this->topic = topic;
    this->type = type;
}

void Client::connect(string ip, string port)
{
    ip::address server_address = ip::make_address(ip);
    ip::port_type server_port = ip::port_type(std::stoi(port));
    ip::tcp::endpoint endpoint(server_address, server_port);
    socket.connect(endpoint);
    initialize_client();
}

void Client::initialize_client()
{
    string message = std::to_string(type);
    message += "--" + topic;

    auto buffer = asio::buffer(message, message.length());
    socket.write_some(buffer);
    socket.wait(socket.wait_write);
};

void Client::disconnect()
{
    socket.close();
}

ClientPublisher::ClientPublisher(string topic) : Client(topic, 1) {}

void ClientPublisher::push_new_message(string message)
{
    boost::system::error_code error_code;

    auto buffer = asio::buffer(message, message.length());
    socket.write_some(buffer, error_code);
}

ClientSubscriber::ClientSubscriber(string topic) : Client(topic, 0) {}

string ClientSubscriber::pull_new_message()
{
    array<char, 1024> char_buffer;
    boost::system::error_code error_code;
    asio::mutable_buffer buffer = asio::buffer(char_buffer, 1024);
    int char_count = socket.read_some(buffer, error_code);
    string message(char_buffer.begin(), char_count);
    return message;
}
