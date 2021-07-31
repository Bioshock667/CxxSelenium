#pragma once
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
//BOOST_LOG_ATTRIBUTE_KEYWORD(tag_attr, "Tag", std::string)
using tcp = net::ip::tcp;
/// A class for the handling of Network-Level HTTP Transactions
class HttpClient
{
public:
	/// A constructor for setting up an HTTP connection
	///  \warning IPv4 and IPv6 addresses not supported
	/// @param url the domain name for the HttpClient to connect to.
	/// @param port the port number for the HttpClient to connect to.
	HttpClient(std::string url, std::string port) :url(url), port(port), resolver(ioc),stream(ioc) {
		slog.add_attribute("Tag",boost::log::attributes::constant< std::string >("Client HTTP"));
	}
	/// A destructor that will terminate the HTTP connection upon call.
	~HttpClient();
	/// Initiate the HTTP connection
	void startConnection();
	/// Sends the provided HTTP request
	http::response<http::string_body> execute(http::request<http::string_body> req);
protected:
	std::string url;
	std::string port;
	boost::log::sources::severity_logger<boost::log::trivial::severity_level> slog;
private:
	net::io_context ioc;
	tcp::resolver resolver;
	beast::tcp_stream stream;
};

