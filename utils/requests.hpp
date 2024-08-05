#include "root_certificates.hpp"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <cstdlib>
#include <iostream>
#include <boost/json.hpp>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
namespace ssl = asio::ssl;
namespace json = boost::json;

using tcp = asio::ip::tcp;
using std::string;

string const host = "www.cse.lk";
string const port = "443";
string const target = "/api/tradeSummary";
int version = 11;
