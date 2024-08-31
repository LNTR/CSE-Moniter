#include "Client.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    std::system("cls");

    string ip = argv[1];
    string port = argv[2];

    Publisher client;
    client.connect(ip, port);

    for (;;)
    {
        string user_input;
        std::getline(std::cin, user_input);
        if (user_input == "terminate")
        {
            client.push_new_message(user_input);
            client.disconnect();
            break;
        }
        else
        {
            user_input += "\n";
            client.push_new_message(user_input);
        }
    }
    return 0;
}