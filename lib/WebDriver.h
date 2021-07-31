#pragma once
#include "By.h"
#include "WebElement.h"
#include "WebDriverCommandExecutor.h"
#include "LocalServerExecutor.h"
#include "Capabilities.h"
#include <string>
#include <vector>
/// An abstraction of an existing WebDriver session.
/** Because this WebDriver is designed to represent a single WebDriver session and the amount of configuration required to initiate one,
 */
class WebDriver 
{
public:
	class LocalBuilder;
	class RemoteBuilder;
	/**
	 * An abstract builder class to provide a common interface for all builder classes to function. 
	 */
	class AbstractBuilder 
	{
	public:
		enum BrowserType { CHROME, FIREFOX, IE, OTHER };
		AbstractBuilder(std::string url) :url(url) {}
		AbstractBuilder(std::string url, std::string port) :url(url), port(port) {}
		/// Configure the builder to provide DesiredCapabilities upon creating a new WebDriver session
		AbstractBuilder* withCapabilities(DesiredCapabilities c);
		/// Configure the builder to create a WebDriver that runs Google Chrome
		AbstractBuilder* chrome() { type = CHROME; return this; }
		/// Configure the builder to create a WebDriver that runs Mozilla FireFox
		AbstractBuilder* firefox() { type = FIREFOX; return this; }
		/// Configure the builder to create a WebDriver that runs Microsoft Internet Explorer
		AbstractBuilder* ie() { type = IE; return this; }
		AbstractBuilder* withBrowser(BrowserType t) { type = t; return this; }
		/// Dynamically cast current pointer as a LocalBuilder pointer
		LocalBuilder* asLocal() { return (LocalBuilder*)this; }
		/// Dynamically cast current pointer as a RemoteBuilder pointer
		RemoteBuilder* asRemote() { return (RemoteBuilder*)this; }
		/// Once needed configuration is provided, create and return a WebDriver instance.
		/// This function will **delete** the current builder object on use so do not continue to use the builder object.
		virtual WebDriver* build() = 0;
	protected:
		std::string url, port;
		BrowserType type;
		DesiredCapabilities c;
	} ;

	/// A builder class for building Local WebDriver instances.
	/** Local WebDrivers are sessions for WebDriver Servers that are executed and hosted on the same machine.  Because of this fact, LocalBuilders need to know
	 * where the right executable for the right type of WebDriver is.  Currently you cannot specify the executable locations for Chrome, FireFox, and IE drivers.
	 * It will try to invoke the correct executable name from the command line.  So make sure to include the path to the executables in the PATH variable.  Otherwise,
	 * you can specify a custom executable.
	 */
	class LocalBuilder : public AbstractBuilder 
	{
	public:
		LocalBuilder() : AbstractBuilder("localhost", "5555"){}
		/**
		 * Provide a path to the executable
		 */
		LocalBuilder* customExecutable(std::string executable) { type = OTHER; custom = executable; return this; }
		/**
		 * Configure the WebDriver's local Selenium server's log level
		 */
		LocalBuilder* withLogLevel(std::string logLevel) { this->logLevel = logLevel; return this; }
		virtual WebDriver* build();
	private:
		std::string custom,logLevel;
	};

	/// A builder for creating Remote WebDriver instances.
	/** Remote WebDrivers are sessions for WebDriver servers that are already running.  The servers could be locally or remotely hosted.  Because of this fact, 
	 * RemoteBuilders need the hostname and port.
	 */
	class RemoteBuilder : public AbstractBuilder 
	{
	public:
		RemoteBuilder(std::string url) : AbstractBuilder(url) {}
		RemoteBuilder(std::string url, std::string port) : AbstractBuilder(url,port){}
		virtual WebDriver* build();
	};
	/**
	 * Deconstruct the WebDriver Instance.
	 * If the WebDriver session is active, it will terminate the session.
	 */
	~WebDriver();
	/// Have the WebDriver browser visit the specified URL.
	///		@param url A valid HTTP URL which must start with "http://" or "https://"
	void get(const std::string& url);
	/// Locate and return the WebElement
	/// 	@param strategy A strategy for finding the web element on the current page
	WebElement findElement(By strategy);
	Capabilities getCapabilities();
	/// Locate and return a list of WebElements
	/// 	@param strategy A strategy for finding the web element on the current page
	std::vector<WebElement> findElements(By strategy);
	/// Get the HTTP URL of the current web page.
	std::string getCurrentURL();
	std::string getTitle();
	/// Terminate the current WebDriver session
	void quit();
	static LocalBuilder* localBuilder() { return new LocalBuilder(); }
	static RemoteBuilder* remoteBuilder(std::string url) { return new RemoteBuilder(url); }
	static RemoteBuilder* remoteBuilder(std::string url, std::string port) { return new RemoteBuilder(url, port); }
private:
	WebDriver(LocalServerExecutor*, DesiredCapabilities, string, string);
	WebDriver(LocalServerExecutor*, WebDriverCommandExecutor*, DesiredCapabilities, string, string);
	void init(DesiredCapabilities c);
	LocalServerExecutor* exec;
	WebDriverCommandExecutor* commander;
	Capabilities caps;
	std::string url;
	std::string port;
	bool terminated = false;
};
