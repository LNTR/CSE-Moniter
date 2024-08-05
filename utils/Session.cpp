#include "session.hpp"

Session::Session()
{
    setup_session();
}

void Session::setup_session()
{
    io_context = std::make_unique<asio::io_context>();
    ssl_context = std::make_unique<ssl::context>(ssl::context::tlsv12_client);
    resolver = std::make_unique<tcp::resolver>(*io_context);
    stream = std::make_unique<ssl::stream<beast::tcp_stream>>(*io_context, *ssl_context);
    load_root_certificates();
};

void Session::load_root_certificates()
{

    std::string cert_path = "./cert.pem";
    std::ifstream cert_file;
    cert_file.open(cert_path);
    std::stringstream buffer;
    buffer << cert_file.rdbuf();

    std::string cert = "# DigiCert Global Root G2\n";
    cert += buffer.str();
    cert_file.close();

    ssl_context->add_certificate_authority(
        boost::asio::buffer(cert.data(), cert.size()));
};

http::response<http::string_body> Session::get(string url)
{
    boost::url_view url_object = boost::urls::parse_uri(url).value();
    auto const results = resolver->resolve(url_object.host(), url_object.port());
    auto &layer = beast::get_lowest_layer(*stream);
    layer.connect(results);
    stream->handshake(ssl::stream_base::client);
    http::request<http::string_body> request{http::verb::get, url_object.path(), HTTP_VERSION};
    request.set(http::field::host, url_object.host());
    request.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    http::write(*stream, request);
    beast::flat_buffer buffer;
    http::response<http::string_body> response;
    http::read(*stream, buffer, response);

    return response;
};
http::response<http::string_body> Session::post(string url)
{
    boost::url_view url_object = boost::urls::parse_uri(url).value();
    auto const results = resolver->resolve(url_object.host(), "443");
    auto &layer = beast::get_lowest_layer(*stream);
    layer.connect(results);
    stream->handshake(ssl::stream_base::client);
    http::request<http::string_body> request{http::verb::post, url_object.path(), HTTP_VERSION};
    request.set(http::field::host, url_object.host());
    request.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    http::write(*stream, request);
    beast::flat_buffer buffer;
    http::response<http::string_body> response;
    http::read(*stream, buffer, response);

    return response;
}
