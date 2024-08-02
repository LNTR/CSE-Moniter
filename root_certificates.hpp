
#ifndef BOOST_BEAST_EXAMPLE_COMMON_ROOT_CERTIFICATES_HPP
#define BOOST_BEAST_EXAMPLE_COMMON_ROOT_CERTIFICATES_HPP

#include <boost/asio/ssl.hpp>
#include <fstream>
#include <string>
#include <iostream>

namespace ssl = boost::asio::ssl;
using std::string, std::cout;
namespace detail
{

    inline void
    load_root_certificates(ssl::context &ctx, boost::system::error_code &ec)
    {

        std::string cert_path = "./cert.pem";
        std::ifstream cert_file;
        cert_file.open(cert_path);
        std::stringstream buffer;
        buffer << cert_file.rdbuf();

        std::string cert = "# DigiCert Global Root G2\n";
        cert += buffer.str();
        cert_file.close();

        ctx.add_certificate_authority(
            boost::asio::buffer(cert.data(), cert.size()), ec);
        if (ec)
            return;
    }

}

inline void
load_root_certificates(ssl::context &ctx, boost::system::error_code &ec)
{
    detail::load_root_certificates(ctx, ec);
}

inline void
load_root_certificates(ssl::context &ctx)
{
    boost::system::error_code ec;
    detail::load_root_certificates(ctx, ec);
    if (ec)
        throw boost::system::system_error{ec};
}

#endif