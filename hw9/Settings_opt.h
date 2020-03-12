#ifndef Settings_h
#define Settings_h
#include <string>
#include <map>
#include <stdexcept>
#include <memory>
#include <iostream>
#include <variant>

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


template <typename T>
class Setting {
	public:
		Setting(string name, T v) : name{name}, value{v} {}
		//virtual ~Setting(){}
		void process(ConfigVariables &cv)
		{
            map<string,T*>* tmp = nullptr; 
            if constexpr (std::is_floating_point_v<T>)
            {
                tmp = &cv.doubleVars;
            }
            else if constexpr (std::is_same<T, bool>::value)
            {
                tmp = &cv.boolVars;
            }
            else
            {
                tmp = &cv.stringVars;
            }

			auto v = tmp->find(name);
			if (v != tmp->end())
			{
				*(v->second) = std::get<T>(value);
			}
			else
			{
				//throw runtime_error("Invalid String Setting: " + name);
				std::cout<<"Invalid String Setting: " <<name<<std::endl;
			}
		}
		//inline static unique_ptr<Setting<T>> factory(string configLine);
	protected:
		string name;
		std::variant<bool,double,std::string> value;
};

void go(string configLine, ConfigVariables &cv)
{
	auto firstSpace = configLine.find_first_of(' ');
	string name{ configLine.substr(0, firstSpace) };
	string rawValue{ configLine.substr(firstSpace + 1) };
	std::cout<<name<<" : "<<rawValue<<std::endl;
	if (rawValue[0] == '"')
	{
		auto tmp =  make_unique<Setting<std::string>>(name, rawValue.substr(1, rawValue.size() - 2));
		tmp->process(cv);
	}
	else if (rawValue == "true")
	{
		auto tmp =  make_unique<Setting<bool>>(name, true);
		tmp->process(cv);
	}
	else if (rawValue == "false")
	{
		auto tmp =  make_unique<Setting<bool>>(name, false);
		tmp->process(cv);
	}
	else
	{
		//std::cout<<rawValue<<std::endl;
		//auto b = rawValue == std::string("false") ? 1:0;
		//std::cout<<b<<std::endl;
		auto tmp = make_unique<Setting<double>>(name, stod(rawValue));
		tmp->process(cv);
	}
}




}
#endif
