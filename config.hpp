#ifndef CONFIG
#define CONFIG

#include <string>
using std::string;
#define HOST "127.0.0.1"

#define SUBSCRIBER_PORT_NUMBER 88
#define PUBLISHER_PORT_NUMBER 89
#define DATABASE_PORT_NUMBER 3306

namespace db_config
{
    string username = "root";
    string password = "root";
    string db_name = "root";
}

#endif