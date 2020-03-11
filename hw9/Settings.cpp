#include <fstream>
#include "Settings.h"

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
	ifstream configs("configs.txt");
	while (getline(configs, line)) {
		Setting::factory(line)->process(configVariables);
	}
	return 0;
}