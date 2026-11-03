#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include "WeatherData.h"

void displayTemperatureGraph(const std::vector<WeatherData>& data, const std::string& periodType, const std::string& period);

#endif // GRAPH_H
