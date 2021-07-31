#define BOOST_TEST_MODULE CppSeleniumTests
#define WIN32_LEAN_AND_MEAN   
#include <boost/test/included/unit_test.hpp>
#include "WebDriver.h"
#include "WebElement.h"
#include "WebDriverException.h"
#include "By.h"
#include "WebDriverException.h"
#include <iostream>
#include <fstream>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/support/date_time.hpp>
namespace utf = boost::unit_test;
namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
void init()
{
    // Construct the sink
    typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;
    boost::shared_ptr< text_sink > sink = boost::make_shared< text_sink >();

    // Add a stream to write log to
    sink->locked_backend()->add_stream(
        boost::make_shared< std::ofstream >("test.log"));

	sink->set_formatter(
		expr::stream
                << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
                << ": <" << expr::attr<std::string>("Tag")
                << "> " << expr::smessage
	);
    // Register the sink in the logging core
    logging::core::get()->add_sink(sink);

	logging::add_common_attributes();
}
void web_driver_canary_test(WebDriver* r, std::string browserName) {
		//WebDriver should throw an exception when given an invalid URL
		BOOST_CHECK_THROW(r->get("www.example.org"), WebDriverException);
		//WebDriver should not throw an exception when given a valid URL
		BOOST_CHECK_NO_THROW(r->get("http://www.example.org"));
		//WebDriver should throw an exeption when given invalid criteria for searching an element
		BOOST_CHECK_THROW(r->findElement(By::tagName("notARealTagName")), WebDriverException);
		//The tagname search strategy should work
		WebElement e = r->findElement(By::tagName("h1"));
		BOOST_TEST(e.getElementText() == "Example Domain");
		//The link text search strategy should work
		WebElement link = r->findElement(By::linkText("More information..."));
		//since the resulting element is valid and clickable.  this should work without exception
		link.click();

		BOOST_CHECK_NO_THROW(r->findElement(By::partialLinkText("About")));
		BOOST_CHECK_NO_THROW(r->findElement(By::id("body")));
		BOOST_CHECK_NO_THROW(r->findElement(By::className("navigation")));
		BOOST_CHECK_NO_THROW(r->findElement(By::css(".navigation td")));
		BOOST_CHECK_NO_THROW(r->findElement(By::xpath("//div/div/h1")));
		auto elements = r->findElements(By::css("#main_right p"));
		BOOST_CHECK(elements.size() == 6);
		//getCapabilities should return a copy of the capabilities taken from the webdriver
		Capabilities fromDriver = r->getCapabilities();
		BOOST_TEST(*fromDriver.browserName == browserName);
		BOOST_TEST(*fromDriver.platformName == "windows");
		r->quit();
		delete r;
}
BOOST_AUTO_TEST_CASE(CapabilitiesTest, *utf::enabled() *utf::label("smoke"))
/* A complete test of all of Capabilites required features*/
{
	//all properties should be empty by default
	Capabilities c;
	BOOST_TEST(!c.browserName.is_initialized());
	BOOST_TEST(!c.browserVersion.is_initialized());
	BOOST_TEST(!c.platformName.is_initialized());
	BOOST_TEST(!c.pageLoadStrategy.is_initialized());
	BOOST_TEST(!c.acceptInsecureCerts.is_initialized());
	BOOST_TEST(!c.setWindowRect.is_initialized());

	//json from an empty Capabilities should just be an empty object
	nlohmann::json emptyJson = c;
	BOOST_TEST(emptyJson.is_object());
	BOOST_TEST(emptyJson.items().begin() == emptyJson.items().end());
	BOOST_TEST(emptyJson.dump() == "{}");

	//Capabilities should be translated from json without issue.  unsupported keys should be skipped
	Capabilities fromJson = "{\"browserName\":\"chrome\",\"browserVersion\":\"85\",\"platformName\":\"windows\",\"notAValue\":\"value\"}"_json;
	BOOST_TEST(*fromJson.browserName == "chrome");
	BOOST_TEST(*fromJson.browserVersion == "85");
	BOOST_TEST(*fromJson.platformName == "windows");
}

BOOST_AUTO_TEST_CASE(FireFoxWebDriverTest, *utf::enabled() *utf::label("smoke"))
{
	init();
	WebDriver* r = WebDriver::localBuilder()->firefox()->build();
	try {
		web_driver_canary_test(r, "firefox");
		std::cout << "WebDriver terminated without issue" << std::endl;
	}
	catch (WebDriverException e) {
		std::cout << "Exception thrown terminating webdriver ..." << std::endl;
		r->quit();
		delete r;
		BOOST_FAIL("Exception " << e.what() << "was thrown!");
	}
	catch (std::exception e) {
		std::cout << "Exception thrown terminating webdriver ..." << std::endl;
		delete r;
		e.what();
		BOOST_FAIL("Exception " << e.what() << "was thrown!");
	}
}

BOOST_AUTO_TEST_CASE(ChromeWebDriverTest, *utf::enabled() *utf::label("smoke"))
{
	WebDriver* r = WebDriver::localBuilder()->chrome()->build();
	try {
		web_driver_canary_test(r, "chrome");
		std::cout << "WebDriver terminated without issue" << std::endl;
	}
	catch (WebDriverException e) {
		std::cout << "Exception thrown terminating webdriver ..." << std::endl;
		r->quit();
		delete r;
		e.what();
		BOOST_FAIL("Exception " << e.what() << "was thrown!");
	}
	catch (std::exception e) {
		std::cout << "Exception thrown terminating webdriver ..." << std::endl;
		r->quit();
		delete r;
		e.what();
		BOOST_FAIL("Exception " << e.what() << "was thrown!");
	}
	//std::cin.get();
}

BOOST_AUTO_TEST_CASE(IEWebDriverTest, *utf::enabled() *utf::label("smoke"))
{
	WebDriver* r = ((WebDriver::LocalBuilder *)WebDriver::localBuilder()->ie())->withLogLevel("INFO")->build();
	try {
		web_driver_canary_test(r, "internet explorer");
		std::cout << "WebDriver terminated without issue" << std::endl;
	}
	catch (WebDriverException e) {
		std::cout << "Exception thrown terminating webdriver ..." << std::endl;
		r->quit();
		delete r;
		e.what();
		BOOST_FAIL("Exception " << e.what() << "was thrown!");
	}
	catch (boost::beast::system_error e) {
		std::cout << "Exception thrown terminating webdriver ..." << std::endl;
		r->quit();
		delete r;
		e.what();
		BOOST_FAIL("Exception " << e.what() << "was thrown!");
	}
	//std::cin.get();
}
BOOST_AUTO_TEST_CASE(RemoteWebDriverTest, *utf::enabled())
{
	WebDriver* r = WebDriver::remoteBuilder("localhost", "4444")->chrome()->build();
	try {
		web_driver_canary_test(r, "chrome");
		std::cout << "WebDriver terminated without issue" << std::endl;
	}
	catch (WebDriverException e) {
		std::cout << "Exception thrown terminating webdriver ..." << std::endl;
		r->quit();
		delete r;
		throw;
	}
	catch (boost::beast::system_error e) {
		std::cout << "Exception thrown terminating webdriver ..." << std::endl;
		r->quit();
		delete r;
		throw;
	}
	//std::cin.get();
}
BOOST_AUTO_TEST_CASE(MultipleDriverTest, *utf::disabled()) 
{
	WebDriver* d1 = WebDriver::localBuilder()->firefox()->build();
	WebDriver* d2 = WebDriver::localBuilder()->chrome()->build();
	d1->get("http://www.yahoo.com");
	d2->get("http://www.google.com");
	d1->findElement(By::linkText("News")).click();
	d2->findElement(By::linkText("About")).click();
	delete d1;
	delete d2;
}