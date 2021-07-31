#pragma once
#include "WebDriverCommandExecutor.h"
#include "Capabilities.h"
#include <nlohmann/json.hpp>
#include "JsonWireClient.h"
#include <string>

class SeleniumGridCommandExecutor : public WebDriverCommandExecutor {
    friend class WebDriver;
    friend class WebElement;
    SeleniumGridCommandExecutor(std::string url, std::string port);
    json handleJsonRequest(boost::beast::http::verb verb, std::string target, json parameters = json(json::value_t::object));
};