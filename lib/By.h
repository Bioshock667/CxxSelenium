#pragma once
#include <string>
using std::string;
/// Used to specify searching strategies for WebElements.
class By
{
public:
	/// search for a WebElement by the ID attribute
	static By id(string value) { return By("css selector", "#" + value); }
	/// search for a WebElement by the class attribute
	static By className(string value) { return By("css selector","." + value); }
	/// search relative to the current context for a WebElement by providing an xpath expression
	static By xpath(string value) {return By("xpath", value);}
	/// search for a WebElement by providing a CSS selector
	static By css(string value) { return By("css selector", value); }
	/// search for a WebElement by the tag name
	static By tagName(string value) { return By("tag name", value);}
	/// search for an anchor(or link) element by providing the text that completely matches its text
	static By linkText(string value) { return By("link text", value); }
	/// search for an anchor(or link) element by providing the text that partial matches its text
	static By partialLinkText(string value) { return By("partial link text", value); }
private:
	string strategy;
	string value;
	By(string strat, string val) : strategy(strat),value(val) {}
	friend class WebDriver;
};

