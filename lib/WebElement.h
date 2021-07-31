#pragma once

#include "WebDriverCommandExecutor.h"
#include <nlohmann/json.hpp>
#include <string>
/// A element that can be found on the current webpage like buttons and inputs.
/** As defined in the [WebDriver Protocol](https://w3c.github.io/webdriver/#elements)
 *  > A web element is an abstraction used to identify an element when it is transported via
 *  > the protocol, between remote and local ends
 *  Use them to perform actions that require specific elements like clicking and validation.
 * 	Equality of WebElements is determined by their [web element reference](https://w3c.github.io/webdriver/#dfn-web-element-reference)
 *  which is designed to uniquely identify the element across all browsing contexts.
 */
class WebElement 
{
	friend class WebDriver;
public:
	bool operator==(const WebElement& other) {	return elementRef == other.elementRef; }
	bool operator!=(const WebElement& other) {	return elementRef != other.elementRef; }
	void click() {	exec->click(elementRef); }
	/// Get the displayed text of the WebElement as a string
	std::string getElementText();
private:
	WebElement(std::string id, std::string reference, WebDriverCommandExecutor* e) :elementId(id), elementRef(reference), exec(e) {}
	std::string elementId,elementRef;
	WebDriverCommandExecutor* exec;
};

