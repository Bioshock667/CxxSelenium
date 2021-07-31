#pragma once

#include "SeleniumGridCommandExecutor.h"
#include "WebDriverException.h"

using nlohmann::json;
SeleniumGridCommandExecutor::SeleniumGridCommandExecutor(std::string url, std::string port): WebDriverCommandExecutor(url, port){}

json SeleniumGridCommandExecutor::handleJsonRequest(boost::beast::http::verb verb, std::string target, json parameters){
	json result;
	if(verb == http::verb::post)
		result = client.executeJsonRequest(verb, "/wd/hub" + target, parameters);
	else
		result = client.executeRequest(verb, "/wd/hub" + target);
	if (result.contains("error")) 
		throw WebDriverException(result);
	else 
		return result;
}