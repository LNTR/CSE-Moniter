#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <cstdlib>
#include <iostream>
#include <boost/json.hpp>
#include <string>
#include <boost/url.hpp>
#include <memory>
#include <fstream>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
namespace ssl = asio::ssl;
namespace json = boost::json;

using tcp = asio::ip::tcp;
using std::string;

class Session
{
public:
    Session();
    http::response<http::string_body> get(string url);
    http::response<http::string_body> post(string url);

private:
    int HTTP_VERSION = 11;
    std::unique_ptr<asio::io_context> io_context;
    std::unique_ptr<ssl::context> ssl_context;
    std::unique_ptr<tcp::resolver> resolver;
    std::unique_ptr<ssl::stream<beast::tcp_stream>> stream;

    void setup_session();

    void load_root_certificates();
};