#include "Capabilities.h"

using std::string;

template<typename T>
boost::optional<T> getFromJson(const nlohmann::json& j, const string& key) {
	if(j.contains(key)){
		return j[key].get<T>();
	} else {
		return boost::none;
	}
}

template<typename T>
void setJsonValue(nlohmann::json& j, const string& key, const boost::optional<T> optProperty) { if (optProperty) j[key] = *optProperty; }

void to_json(nlohmann::json& j, const Capabilities& c)
{
	j = nlohmann::json(nlohmann::json::value_t::object);
	setJsonValue(j, "browserName", c.browserName);
	setJsonValue(j, "browserVersion", c.browserVersion);
	setJsonValue(j, "browserName", c.browserName);
	setJsonValue(j, "acceptInsecureCerts", c.acceptInsecureCerts);

}
void from_json(const nlohmann::json& j, Capabilities& c)
{
	//every property must be set or else and not initialized exception is thrown by optional class.  I don't know why.  I set the constructor to initialize each properties with boost::none
	c.browserName = getFromJson<string>(j,"browserName");
	c.browserVersion = getFromJson<string>(j, "browserVersion");
	c.platformName = getFromJson<string>(j, "platformName");
	c.acceptInsecureCerts = getFromJson<bool>(j, "acceptInsecureCerts");
}
void to_json(nlohmann::json& j, const DesiredCapabilities& d){
	j = nlohmann::json(nlohmann::json::value_t::object);
	setJsonValue(j, "alwaysMatch", d.required);
	setJsonValue(j, "firstMatch", d.firstMatch);
}

void from_json(const nlohmann::json& j, DesiredCapabilities& d){
	d.required = getFromJson<Capabilities>(j, "alwaysMatch");
	d.firstMatch = getFromJson<std::vector<Capabilities>>(j, "firstMatch");
}