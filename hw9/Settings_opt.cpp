#include <fstream>
#include "Settings_opt.h"

using namespace std;
using namespace mpcs;

// Configs with default values
double maxVoltage{100};
double maxCurrent{5};
string deviceName{"unspecified"};
bool enableHyperdrive{false};

ConfigVariables configVariables = {
	{ { "deviceName", &deviceName } },
    { { "enableHyperdrive", &enableHyperdrive } },
    { { "maxVoltage", &maxVoltage }, { "maxCurrent", &maxCurrent } }
};

int main()
{
	string line;
    for (auto& i : configVariables.doubleVars)
    {
        //cout<<i.first<<" : "<<i.second<<endl;
    }
	ifstream configs("configs.txt");
	while (getline(configs, line)) {
		go(line,configVariables);
	}
	return 0;
}
