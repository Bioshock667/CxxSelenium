#pragma once
#include "LocalServerExecutor.h"
/// A Microsoft Internet Explorer based implementation of LocalServerExecutor
class IEDriverExecutor : public LocalServerExecutor
{
public:
	IEDriverExecutor() : LocalServerExecutor("IEDriverServer.exe") {}
	void setPort(const std::string& port) { addArgument("/port=" + port); }
	virtual void setLogLevel(const std::string& level) { addArgument("/log-level=" + level); }
	std::string defaultPort() { return "5555"; }
};

