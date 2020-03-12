#ifndef Settings_h
#define Settings_h
#include <string>
#include <map>
#include <stdexcept>
#include <memory>
#include <iostream>

using std::string;
using std::map;
using std::runtime_error;
using std::unique_ptr;
using std::make_unique;
using std::stod;

namespace mpcs {
struct ConfigVariables {
	map<string, string *> stringVars;
	map<string, bool *> boolVars;
	map<string, double *> doubleVars;
};

class Setting {
public:
	Setting(string name) : name{name} {}
	virtual void process(ConfigVariables const &cv) = 0;
	inline static unique_ptr<Setting> factory(string configLine);
protected:
	string name;
};

class StringSetting : public Setting {
public:
	StringSetting(string name, string value) : Setting{name}, value{value} {}

	virtual void process(ConfigVariables const &cv) {
		auto v = cv.stringVars.find(name);
		if (v != cv.stringVars.end())
			*v->second = value;
		else 
			throw runtime_error("Invalid String Setting: " + name);
	}
private:
	string value;
};

class BoolSetting : public Setting {
public:
	BoolSetting(string name, bool value) : Setting{ name }, value{ value } {}
	virtual void process(ConfigVariables const &cv) {
		auto v = cv.boolVars.find(name);
		if (v != cv.boolVars.end())
			*v->second = value;
		else
			throw runtime_error("Invalid String Setting: " + name);
	}
private:
	bool value;
};

class DoubleSetting : public Setting {
public:
	DoubleSetting(string name, double value) : Setting{ name }, value{ value } {}
	virtual void process(ConfigVariables const &cv) {
		auto v = cv.doubleVars.find(name);
		if (v != cv.doubleVars.end())
			*v->second = value;
		else
			throw runtime_error("Invalid String Setting: " + name);
	}
private:
	double value;
};

inline unique_ptr<Setting>
Setting::factory(string configLine)
{
	auto firstSpace = configLine.find_first_of(' ');
	string name{ configLine.substr(0, firstSpace) };
	string rawValue{ configLine.substr(firstSpace + 1) };
    std::cout<<name<<" : "<<rawValue<<std::endl;
	if (rawValue[0] == '"')
		return make_unique<StringSetting>(name, rawValue.substr(1, rawValue.size() - 2));
	else if (rawValue == "true")
		return make_unique<BoolSetting>(name, true);
	else if (rawValue == "false")
		return make_unique<BoolSetting>(name, false);
	else
		return make_unique<DoubleSetting>(name, stod(rawValue));
}
}
#endif
