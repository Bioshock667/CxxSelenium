#include "LocalServerExecutor.h"
#include <thread>
#include <chrono>
#include <iostream>
using boost::log::trivial::severity_level;
LocalServerExecutor::LocalServerExecutor():processName(""){slog.add_attribute("Tag",boost::log::attributes::constant< std::string >("Local Server"));}

LocalServerExecutor::LocalServerExecutor(std::string pName) : processName(pName) {slog.add_attribute("Tag",boost::log::attributes::constant< std::string >("Local Server"));}

void LocalServerExecutor::addArgument(std::string arg) {args.push_back(arg);}
void LocalServerExecutor::setOutputFile(std::string fileName){this->fileName = fileName;}
int LocalServerExecutor::start()
{
	if (processName.empty())
		return 1;
	std::string procArgs = processName;
	for (std::string s : args) 
		procArgs.append(" " + s);
	try {
	if(!fileName.empty())
		c = proc::child(procArgs, proc::std_out > fileName);
	 else 
		c = proc::child(procArgs,proc::std_err > stderr, proc::std_out > stdout);
	} catch (proc::process_error e){
		BOOST_LOG_SEV(slog, severity_level::error) << e.what();
		return 1;
	}
	BOOST_LOG_SEV(slog, severity_level::info) << "Process "+procArgs+" has started";
	std::this_thread::sleep_for(std::chrono::seconds(2));
	return 0;
}

int LocalServerExecutor::stop() 
{
	if (processName.empty())
		return 1;
	c.terminate();
	BOOST_LOG_SEV(slog, severity_level::info) << "child process stopped";
	return c.exit_code();

}

bool LocalServerExecutor::isRunning() {	return c.running();}