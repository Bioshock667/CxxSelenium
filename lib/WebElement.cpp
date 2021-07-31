#include "WebElement.h"

std::string WebElement::getElementText() 
{
	nlohmann::json result = exec->getElementText(elementRef);
	return result.get<std::string>();
}