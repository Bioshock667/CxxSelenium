#include "WebDriverException.h"

WebDriverException::WebDriverException() {}
WebDriverException::WebDriverException(const nlohmann::json j) 
{
	name = j.at("error").get<std::string>();
	message = j.at("message").get<std::string>();
	stacktrace = j.at("stacktrace").get<std::string>();
	reason = "Error Type: " + name + "\nMessage: " + message + "\nStack Trace: " + stacktrace;
}
WebDriverException::~WebDriverException() {  }

char const* WebDriverException::what() const { return reason.c_str(); }