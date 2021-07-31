#pragma once

#include "Capabilities.h"
#include <nlohmann/json.hpp>
#include "JsonWireClient.h"
#include <string>

class WebDriverCommandExecutor
{
	friend class WebDriver;
	friend class WebElement;
	void startConnection();
	Capabilities newSession(const nlohmann::json& capabilites);
	void closeSession();
	void goToURL(std::string url);
	json findElement(std::string strategy, std::string value);
	json findElements(std::string strategy, std::string value);
	void click(std::string elementId);
	json getElementText(std::string elementId);
	json getCurrentURL();
	json getTitle();
	virtual json handleJsonRequest(boost::beast::http::verb verb, std::string target, json parameters = json(json::value_t::object));

	protected:
	WebDriverCommandExecutor(std::string url, std::string port);
	std::string sessionId;
	JsonWireClient client;
	std::string url;
	std::string port;
};