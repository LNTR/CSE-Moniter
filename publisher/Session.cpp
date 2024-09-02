#ifndef SESSION
#define SESSION
#include "Session.hpp"
#endif

Session::Session()
{
    setup_session();
}

void Session::setup_session()
{
    io_context = std::make_unique<asio::io_context>();
    ssl_context = std::make_unique<ssl::context>(ssl::context::tlsv12_client);
    resolver = std::make_unique<tcp::resolver>(*io_context);

    load_root_certificates();
};

void Session::load_root_certificates()
{

    std::string cert_path = "./cert.pem";
    std::ifstream cert_file;
    cert_file.open(cert_path);
    std::stringstream buffer;
    buffer << cert_file.rdbuf();

    std::string cert = "# DigiCert Global Root G2\n"
                       "-----BEGIN CERTIFICATE-----\n"
                       "MIIDjjCCAnagAwIBAgIQAzrx5qcRqaC7KGSxHQn65TANBgkqhkiG9w0BAQsFADBh\n"
                       "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
                       "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\n"
                       "MjAeFw0xMzA4MDExMjAwMDBaFw0zODAxMTUxMjAwMDBaMGExCzAJBgNVBAYTAlVT\n"
                       "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n"
                       "b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IEcyMIIBIjANBgkqhkiG\n"
                       "9w0BAQEFAAOCAQ8AMIIBCgKCAQEAuzfNNNx7a8myaJCtSnX/RrohCgiN9RlUyfuI\n"
                       "2/Ou8jqJkTx65qsGGmvPrC3oXgkkRLpimn7Wo6h+4FR1IAWsULecYxpsMNzaHxmx\n"
                       "1x7e/dfgy5SDN67sH0NO3Xss0r0upS/kqbitOtSZpLYl6ZtrAGCSYP9PIUkY92eQ\n"
                       "q2EGnI/yuum06ZIya7XzV+hdG82MHauVBJVJ8zUtluNJbd134/tJS7SsVQepj5Wz\n"
                       "tCO7TG1F8PapspUwtP1MVYwnSlcUfIKdzXOS0xZKBgyMUNGPHgm+F6HmIcr9g+UQ\n"
                       "vIOlCsRnKPZzFBQ9RnbDhxSJITRNrw9FDKZJobq7nMWxM4MphQIDAQABo0IwQDAP\n"
                       "BgNVHRMBAf8EBTADAQH/MA4GA1UdDwEB/wQEAwIBhjAdBgNVHQ4EFgQUTiJUIBiV\n"
                       "5uNu5g/6+rkS7QYXjzkwDQYJKoZIhvcNAQELBQADggEBAGBnKJRvDkhj6zHd6mcY\n"
                       "1Yl9PMWLSn/pvtsrF9+wX3N3KjITOYFnQoQj8kVnNeyIv/iPsGEMNKSuIEyExtv4\n"
                       "NeF22d+mQrvHRAiGfzZ0JFrabA0UWTW98kndth/Jsw1HKj2ZL7tcu7XUIOGZX1NG\n"
                       "Fdtom/DzMNU+MeKNhJ7jitralj41E6Vf8PlwUHBHQRFXGU7Aj64GxJUTFy8bJZ91\n"
                       "8rGOmaFvE7FBcf6IKshPECBV1/MUReXgRPTqh5Uykw7+U0b6LJ3/iyK5S9kJRaTe\n"
                       "pLiaWN0bfVKfjllDiIGknibVb63dDcY3fe0Dkhvld1927jyNxF1WW6LZZm6zNTfl\n"
                       "MrY=\n"
                       "-----END CERTIFICATE-----\n";
    // std::string cert = buffer.str();
    cert_file.close();
    boost::system::error_code ec;
    ssl_context->add_certificate_authority(
        boost::asio::buffer(cert.data(), cert.size()), ec);
    if (ec)
    {
        std::cout << ec;
    }
};

http::response<http::string_body> Session::get(string url)
{
    auto stream = std::make_unique<ssl::stream<beast::tcp_stream>>(*io_context, *ssl_context);
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
    auto stream = std::make_unique<ssl::stream<beast::tcp_stream>>(*io_context, *ssl_context);
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
