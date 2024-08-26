#include <boost/mysql.hpp>
#include <boost/asio.hpp>
#include <memory>
#include <vector>
#include <format>

namespace mysql = boost::mysql;
namespace asio = boost::asio;
namespace ssl = asio::ssl;
namespace ip = asio::ip;

using tcp = asio::ip::tcp;
using std::string;
using std::vector;

class MySqlModel
{

public:
    MySqlModel();
    ~MySqlModel();
    bool execute_query(string query, vector<string> data);

private:
    asio::io_context io_context;
    std::unique_ptr<mysql::tcp_ssl_connection> connection;
    void set_up_connection();
};
