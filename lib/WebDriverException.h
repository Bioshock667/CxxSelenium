#pragma once
#include <exception>
#include <nlohmann/json.hpp>
#include <string>
/// A class for throwing errors sent from the Selenium WebDriver
class WebDriverException : public std::exception
{
public:
	WebDriverException();
	WebDriverException(const nlohmann::json j);
	~WebDriverException();
	virtual char const* what() const;
private:
	std::string name;
	std::string message;
	std::string stacktrace;
	std::string reason;
};


