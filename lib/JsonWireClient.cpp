#include "JsonWireClient.h"
#include <iostream>
using boost::log::trivial::severity_level;
json JsonWireClient::executeJsonRequest(boost::beast::http::verb verb, std::string target, const json& parameters) 
{
	JsonRequest req(verb, target, 11);
	req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
	req.set(http::field::host, url);
	req.set(http::field::content_type, "application/json; charset=utf-8");
	std::string payloadString = parameters.dump();
	if (!parameters.is_null())
		req.body() = payloadString;
	req.prepare_payload();

	BOOST_LOG_SEV(slog, severity_level::info) << "Ready to send request " << req;
	JsonResponse res = execute(req);
	BOOST_LOG_SEV(slog, severity_level::info) << "Response is " << res;

	return json::parse(res.body()).at("value");
}