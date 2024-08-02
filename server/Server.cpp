#include "Server.hpp"
#include <boost/algorithm/string.hpp>

using std::string, std::move, ip::tcp;

NotificationQueue global_notification_queue;

ServerPublisher::ServerPublisher(string topic, tcp::socket socket_) : socket(move(socket_))
{
    this->topic = topic;
    this->notification_queue = &global_notification_queue;
};

void ServerPublisher::read_new_message()
{
    array<char, 1024> char_buffer;
    boost::system::error_code error_code;
    asio::mutable_buffer buffer = asio::buffer(char_buffer, 1024);
    int char_count = socket.read_some(buffer, error_code);
    string message(char_buffer.begin(), char_count);

    if (message.length() > 1)
    {
        publish_message(message);
    }
}

void ServerPublisher::publish_message(string message)
{
    Notification aspect = {topic, message};
    notification_queue->push_new_notification(aspect);
}

ServerSubscriber::ServerSubscriber(string topic, tcp::socket socket_) : socket(move(socket_))
{
    this->topic = topic;
    this->notification_queue = &global_notification_queue;
    this->notification_queue->attach(this);
}

ServerSubscriber::~ServerSubscriber()
{
    this->notification_queue->detach(this);
}

void ServerSubscriber::update(Subject *changed_subject)
{
    if (notification_queue == changed_subject)
    {
        boost::system::error_code error_code;

        Notification new_notification = notification_queue->pull_new_notification();

        if (new_notification.topic == topic)
        {
            asio::mutable_buffer buffer = asio::buffer(new_notification.message, new_notification.message.length());
            socket.write_some(buffer, error_code);
        }
    }
}

ClientMetaData get_meta_data(tcp::socket &socket)
{
    array<char, 1024> char_buffer;
    boost::system::error_code error_code;
    asio::mutable_buffer buffer = asio::buffer(char_buffer, 1024);
    int char_count = socket.read_some(buffer, error_code);
    string message(char_buffer.begin(), char_count);
    vector<string> split_vector;
    boost::split(split_vector, message, boost::is_any_of("--"), boost::token_compress_on);
    string type = split_vector.at(0);
    string topic = split_vector.at(1);
    return ClientMetaData{topic, type};
}