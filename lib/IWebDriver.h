// CppSelenium.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "IWebElement.h"
#include "By.h"
#include <boost/regex.hpp>
// TODO: This is an example of a library function
class IWebDriver {
	virtual IWebElement findElement(By strategy) = 0;
	virtual std::vector<IWebElement> findElements(By strategy) = 0;
};


