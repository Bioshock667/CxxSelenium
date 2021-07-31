#pragma once
#include "nlohmann/json.hpp"
#include <boost/optional.hpp>
#include <string>



using std::string;
using boost::optional;

/// A set of configuration values and properties for an existing WebDriver session.
/** Every WebDriver session has set of values that represent the state of the WebDriver session.  This is suitable for validating the properties of the session,
 * for example checking what browser you are using.
 */ 
struct Capabilities
{
	optional<string> browserName;
	optional<string> browserVersion;
	optional<string> platformName;
	optional<bool> acceptInsecureCerts;
	optional<bool> setWindowRect;
	optional<string> pageLoadStrategy;
};
/// A set of configuration values and properties that a client wants for a potential WebDriver session.
struct DesiredCapabilities {
	optional<Capabilities> required;
	optional <std::vector<Capabilities>> firstMatch;
	
};
struct Timeouts {
	optional<int> scriptTimeout;
	optional<int> pageLoadTimeout;
	optional<int> implicitWaitTimeout;
};

DesiredCapabilities requireCaps(Capabilities c);
DesiredCapabilities optionalCaps(Capabilities c);
//Yes, I am rewriting Nlohmann's macro so it can work with boost::optional if the value is not there
//#define LEMANEK_JSON_TO(v1) if(nlohmann_json_t.v1) nlohmann_json_j[#v1] = *nlohmann_json_t.v1;
//#define LEMANEK_JSON_FROM(v1) if(nlohmann_json_j.contains(#v1)) nlohmann_json_t.v1.assign(nlohmann_json_j.at(#v1));
//
//#define LEMANEK_DEFINE_TYPE_OPTIONAL_NON_INTRUSIVE(Type, ...)  \
//    inline void to_json(nlohmann::json& nlohmann_json_j, const Type& nlohmann_json_t) {nlohmann_json_j = nlohmann::json(nlohmann::json::value_t::object); NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(LEMANEK_JSON_TO, __VA_ARGS__)) } \
//    inline void from_json(const nlohmann::json& nlohmann_json_j, Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(LEMANEK_JSON_FROM, __VA_ARGS__)) }
//
//LEMANEK_DEFINE_TYPE_OPTIONAL_NON_INTRUSIVE(Capabilities, browserName, browserVersion, platformName)
void to_json(nlohmann::json& j, const DesiredCapabilities& d);

void from_json(const nlohmann::json& j, DesiredCapabilities& d);

void to_json(nlohmann::json& j, const Capabilities& c);

void from_json(const nlohmann::json& j, Capabilities& c);
