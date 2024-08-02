#include "client/Client.hpp"

int main(int argc, char **argv)
{
    std::system("cls");
    string ip = argv[1];
    string port = argv[2];
    string topic = argv[3];

    ClientSubscriber client(topic);
    client.connect(ip, port);

    for (;;)
    {
        string message = client.pull_new_message();
        std::cout << message;
        if (message == "terminate")
        {
            client.disconnect();
            break;
        }
    }
    return 0;
}