#pragma once
#include "LocalServerExecutor.h"
/// A Mozilla Firefox based implementation of LocalServerExecutor
class FirefoxDriverExecutor : public LocalServerExecutor
{
public:
    FirefoxDriverExecutor() : LocalServerExecutor("geckodriver.exe") {}
    void setPort(const std::string& port) { addArgument("--port " + port); }
    void setLogLevel(const std::string& level) { addArgument("--log "+level); }
    std::string defaultPort() { return "4444"; }
};

