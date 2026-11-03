#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <vector>
#include <string>
#include "Candlestick.h"

struct WeatherData {
    std::string timestamp;
    float temperature;
};

std::vector<WeatherData> readCSV(const std::string& filename, const std::string& country_code);
std::vector<WeatherData> filterDataByYear(const std::vector<WeatherData>& data, int year);
std::vector<Candlestick> computeMonthlyCandlestickData(const std::vector<WeatherData>& data);

#endif // WEATHERDATA_H
