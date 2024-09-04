#include "MySqlModel.hpp"
#include "config.hpp"

namespace db_config
{
    string host = "127.0.0.1";
    string username = "root";
    string password = "root";
    string db_name = "ExampleDB";
}

MySqlModel::MySqlModel() : io_context()
{
    set_up_connection();
};

MySqlModel::~MySqlModel()
{
    connection->close();
}

void MySqlModel::set_up_connection()
{
    ssl::context ssl_context(ssl::context::tls_client);
    connection = std::make_unique<mysql::tcp_ssl_connection>(io_context, ssl_context);

    ip::address server_address = ip::make_address(db_config::host);
    ip::port_type server_port = ip::port_type(DATABASE_PORT_NUMBER);
    ip::tcp::endpoint endpoint(server_address, server_port);
    mysql::handshake_params params(db_config::username, db_config::password, db_config::db_name);
    connection->connect(endpoint, params);
}

mysql::results MySqlModel::execute_query(string query, vector<string> data)
{
    query = std::format(R"%({})%", query);
    mysql::statement statement = connection->prepare_statement(query);
    mysql::results result;

    connection->execute(statement.bind(), result);
    return result;
}
