#include "Publisher.hpp"
#include "Session.hpp"
#include <iostream>
#include <chrono>
#include <thread>

int main(int argc, char **argv)
{
    std::system("cls");

    string ip = argv[1];
    string port = argv[2];

    Publisher client;
    Session session;

    client.connect(ip, port);

    for (;;)
    {

        auto results = session.post("www.cse.lk/api/tradeSummary");
        string message = results.body();
        client.push_new_message(message);
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    return 0;
}