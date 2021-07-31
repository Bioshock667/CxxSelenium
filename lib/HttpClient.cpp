#include "HttpClient.h"
#include <iostream>
using boost::log::trivial::severity_level;
void HttpClient::startConnection()
{
    BOOST_LOG_SEV(slog, severity_level::info) << "initiating connection at " << url << ":" << port << std::endl;
    auto results = resolver.resolve(url, port);
    auto endpoint = stream.connect(results);
    BOOST_LOG_SEV(slog, severity_level::info) << "Connection successful" << std::endl;
}

HttpClient::~HttpClient()
{
    stream.socket().shutdown(tcp::socket::shutdown_both);
}
http::response<http::string_body> HttpClient::execute(const http::request<http::string_body> req)
{
    http::response<http::string_body> res;
    beast::error_code ec;
    http::write(stream, req);
    beast::flat_buffer buf;
    http::read(stream, buf, res);
    return res;
}
