#pragma once
class IWebElement
{
	virtual void click() = 0;
	virtual std::string getElementText() = 0;
};

