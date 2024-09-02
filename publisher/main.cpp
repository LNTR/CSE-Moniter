#include "Publisher.hpp"
#include "Session.hpp"
#include <iostream>
#include <chrono>
#include <thread>

int main(int argc, char **argv)
{
    // std::system("cls");

    string ip = "127.0.0.1";
    string port = "89";

    Publisher client;

    client.connect(ip, port);
    Session session;

    for (;;)
    {

        auto results = session.post("https://www.cse.lk/api/tradeSummary");
        string message = results.body();
        client.push_new_message(message);
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    return 0;
}