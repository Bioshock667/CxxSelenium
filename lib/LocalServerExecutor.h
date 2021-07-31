#pragma once

#include <boost/asio.hpp>
#include <boost/process.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <string>
#include <vector>

namespace proc = boost::process;
namespace async = boost::asio;

/// A class that executes and maintains the status of locally-run Selenium WebDriver servers
/** %By instantiating the class with the name of the executable, the user can use LocalServerExecutor to manage settings, run status, and logs of the server.
 * The class is abstract due to the myriad of different ways to passing properties to different properties like port number.  If a user wishes to implement their
 * own LocalServerExecutor they must provide their own way of passing parameters.
 * \warn do not use the "set" methods after calling start().  the "set" methods add arguments that will be passed to the process upon start.  Thus the new properties will not apply.
 */
class LocalServerExecutor
{
public:
	/// Initiate with a blank executable name or path.  
	/// \warning Do not execute without setting a name
	LocalServerExecutor();
	/// Initiate with a given executable path.
	LocalServerExecutor(std::string pName);
	// DO NOT COPY.  Each LocalServerExecutor maintains a process which must be monitored and terminated upon deletion.
	LocalServerExecutor(const LocalServerExecutor&) = delete;
	// Moving is fine.
	LocalServerExecutor(LocalServerExecutor&& other) : processName(std::move(other.processName)),args(std::move(other.args)), c(std::move(other.c)) {}
	/// Pass an argument that the LocalServerExecutor will pass to the Selenium server process upon starting the process.
	void addArgument(std::string arg);
	/// Set the port number of the Selenium server.
	virtual void setPort(const std::string& port) = 0;
	/// Set the log level of the Selenium server.
	virtual void setLogLevel(const std::string& level) = 0;
	/// Set the filename where server output is directed.  Otherwise it will print to stdout.
	void setOutputFile(std::string fileName);
	/// Return the default port number of the Selenium server bring run.
	virtual std::string defaultPort() = 0;
	/// Run the Selenium server locally
	int start();
	/// Terminate the Selenium server
	int stop();
	/// Check if the Selenium server is currently running.
	bool isRunning();
private:
	std::string processName;
	std::vector<std::string> args;
	std::string fileName;
	proc::child c;
	boost::log::sources::severity_logger<boost::log::trivial::severity_level> slog;
};