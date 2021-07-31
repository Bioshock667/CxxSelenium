#pragma once
#include "LocalServerExecutor.h"
/// A Google Chrome based implementation of LocalServerExecutor
class ChromeDriverExecutor :  public LocalServerExecutor
{
public:
	ChromeDriverExecutor() : LocalServerExecutor("chromedriver.exe") {}
	void setPort(const std::string& port) { addArgument("--port=" + port); }
	void setLogLevel(const std::string& level) { addArgument("--log-level=" + level); }
	std::string defaultPort() { return "9515"; }
};

