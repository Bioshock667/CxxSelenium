
#include "WebDriver.h"
#include "ChromeDriverExecutor.h"
#include "FirefoxDriverExecutor.h"
#include "IEDriverExecutor.h"
#include "SeleniumGridCommandExecutor.h"
#include <iostream>
#include <utility>

//WebDriver::WebDriver() : WebDriver(Capabilities()) {}
//WebDriver::WebDriver(Capabilities c) :exec(new ChromeDriverExecutor()),url("localhost"), port("5555"), commander("localhost", "5555"){init(c);}
void WebDriver::init(DesiredCapabilities c)
{
    // remote instances will have a null local server executor
    if (exec) {
        exec->setPort(port);
        exec->start();
    }
    commander->startConnection();
    caps = commander->newSession(c);
}
WebDriver::~WebDriver() {
    if (!terminated)
        quit();
    delete exec;
    delete commander;
}
Capabilities WebDriver::getCapabilities() {  return caps;}
void WebDriver::get(const std::string& url) {  commander->goToURL(url);}
//webdriver server will return something like this to represent an element   {"value":{"element-6066-11e4-a52e-4f735466cecf":"ab26b4fa-7322-443f-a77d-d058ee524447"}} the key of value I presume is the unique id for the session.  The value is the reference that is global for all sessions
WebElement WebDriver::findElement(By strategy)
{
    json elements = commander->findElement(strategy.strategy, strategy.value);
    auto first = elements.items().begin();
    return WebElement(first.key(),first.value(), commander);
}

std::vector<WebElement> WebDriver::findElements(By strategy)
{
    json elements = commander->findElements(strategy.strategy, strategy.value);
    std::vector<WebElement> result;
    for (auto iter = elements.begin(); iter != elements.end(); ++iter)
    {
        auto firstPair = (*iter).items().begin();
        result.push_back(WebElement(firstPair.key(), firstPair.value(), commander));
    }
    return result;
}
std::string WebDriver::getCurrentURL() {
    return commander->getCurrentURL().get<std::string>();
}
std::string WebDriver::getTitle() {
    return commander->getTitle().get<std::string>();
}
WebDriver::WebDriver(LocalServerExecutor* exe, DesiredCapabilities c, string url, string port) : exec(exe), commander(new WebDriverCommandExecutor(url, port)), url(url), port(port) { init(c); }
WebDriver::WebDriver(LocalServerExecutor* exe, WebDriverCommandExecutor* com, DesiredCapabilities c, string url, string port) : exec(exe), commander(com), url(url), port(port) { init(c); }
void WebDriver::quit() {
    terminated = true;
    try { commander->closeSession(); }
    catch (boost::beast::system_error e) 
    {
        std::cerr << "Warning: failed to close session due to system error because " << e.what() << std::endl;
    }
    if(exec)
        exec->stop();
}



//Builder Methods
WebDriver::AbstractBuilder* WebDriver::AbstractBuilder::withCapabilities(DesiredCapabilities c) { this->c = c; return this; }

WebDriver* WebDriver::LocalBuilder::build() {
    LocalServerExecutor* e = nullptr;
    switch (type) {
    case CHROME:
        e = new ChromeDriverExecutor();
        e->setOutputFile("chrome.log");
        break;
    case IE:
        e = new IEDriverExecutor();
        e->setOutputFile("ie.log");
        break;
    case FIREFOX:
        e = new FirefoxDriverExecutor();
        e->setOutputFile("firefox.log");
        break;
    case OTHER:
        break;
    }
    if (!logLevel.empty())
        e->setLogLevel(logLevel);
    string p;
    if (this->port.empty())
        p = e->defaultPort();
    else
        p = this->port;
    WebDriver* d = new WebDriver(e, c, "localhost", p);
    delete this;
    return d;
}

WebDriver* WebDriver::RemoteBuilder::build() {
    Capabilities cap;
    if(this->c.required)
        cap = *c.required;
    switch (this->type)
    {
    case WebDriver::AbstractBuilder::CHROME:
        cap.browserName = "chrome";
        break;
    case WebDriver::AbstractBuilder::FIREFOX:
        cap.browserName = "firefox";
        break;
    case WebDriver::AbstractBuilder::IE:
        cap.browserName = "internetexplorer";
        break;
    case WebDriver::AbstractBuilder::OTHER:
        break;
    default:
        break;
    }
    c.required = cap;
    WebDriverCommandExecutor* com = new SeleniumGridCommandExecutor(url,port);
    return new WebDriver(nullptr, com, c, url, port);
}