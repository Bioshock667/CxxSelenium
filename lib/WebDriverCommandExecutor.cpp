
#include "WebDriverCommandExecutor.h"
#include "WebDriverException.h"
#include <boost/beast/http.hpp>
#include <boost/beast/core.hpp>
#include <iostream>

namespace http = boost::beast::http;
using nlohmann::json;
typedef  http::request<http::string_body> sRequest;
typedef http::response<http::string_body> sResponse;

WebDriverCommandExecutor::WebDriverCommandExecutor(std::string url, std::string port):client(url,port),url(url),port(port) {}

void WebDriverCommandExecutor::startConnection() {client.startConnection();}

json WebDriverCommandExecutor::handleJsonRequest(boost::beast::http::verb verb, std::string target, json parameters )
{
	json result;
	if(verb == http::verb::post)
		result = client.executeJsonRequest(verb, target, parameters);
	else
		result = client.executeRequest(verb,target);
	if (result.contains("error")) 
		throw WebDriverException(result);
	else 
		return result;
}
Capabilities WebDriverCommandExecutor::newSession(const json& capabilites)
{
	json parameters(json::value_t::object);
	parameters["capabilities"] = capabilites;
	json newSession = handleJsonRequest(http::verb::post,"/session", parameters);
	sessionId = newSession["sessionId"].get<std::string>();
	Capabilities c = newSession["capabilities"].get<Capabilities>();
	return c;
}

void WebDriverCommandExecutor::closeSession() 
{
	handleJsonRequest(http::verb::delete_, "/session/" + sessionId);
}

void WebDriverCommandExecutor::goToURL(std::string url) 
{
	json parameters;
	parameters["url"] = url;
	handleJsonRequest(http::verb::post, "/session/" + sessionId + "/url", parameters);
}
json WebDriverCommandExecutor::findElement(std::string strategy, std::string value)
{
	json params;
	params["using"] = strategy;
	params["value"] = value;
	json result = handleJsonRequest(http::verb::post, "/session/" + sessionId + "/element", params);
	return result;
}
json WebDriverCommandExecutor::findElements(std::string strategy, std::string value)
{
	json params;
	params["using"] = strategy;
	params["value"] = value;
	json result = handleJsonRequest(http::verb::post, "/session/" + sessionId + "/elements", params);
	return result;
}
void WebDriverCommandExecutor::click(std::string elementId)
{
	handleJsonRequest(http::verb::post, "/session/" + sessionId + "/element/" + elementId + "/click");
}
json WebDriverCommandExecutor::getElementText(std::string elementId) 
{
	return handleJsonRequest(http::verb::get, "/session/" + sessionId + "/element/" + elementId + "/text");
}
json WebDriverCommandExecutor::getCurrentURL(){
	return handleJsonRequest(http::verb::get, "/session/"+ sessionId + "/url");
}
json WebDriverCommandExecutor::getTitle(){
	return handleJsonRequest(http::verb::get, "/session/"+sessionId + "/title");
}