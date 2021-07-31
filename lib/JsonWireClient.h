#pragma once
#include "HttpClient.h"
#include <nlohmann/json.hpp>
#include <boost/beast/http.hpp>

using nlohmann::json;
typedef boost::beast::http::request<boost::beast::http::string_body> JsonRequest;
typedef boost::beast::http::response<boost::beast::http::string_body> JsonResponse;
/// A class for the handling of Application-Level JSON Wire Protocol.
class JsonWireClient : public HttpClient
{
public:
	JsonWireClient(std::string url, std::string port) : HttpClient(url, port) {}
	/// Sends a JSON Wire request with the provided JSON object as the body.
	/** @param verb an HTTP verb such as GET or POST
	 *  @param target the full HTTP path needed to execute the JSON Wire call
	 *  @param parameters a JSON object that will be passed string encoded in the request body.
	 */
	json executeJsonRequest(boost::beast::http::verb verb, std::string target, const json& parameters);

	/// Sends a JSON Wire request with an empty body
	/** @param verb an HTTP verb such as GET or POST
	 *  @param target the full HTTP path needed to execute the JSON Wire call
	 */
	json executeRequest(boost::beast::http::verb verb, std::string target) {return executeJsonRequest(verb, target, json());}

};

