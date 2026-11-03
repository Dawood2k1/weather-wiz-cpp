#ifndef TEMPERATUREPREDICTOR_H
#define TEMPERATUREPREDICTOR_H

#include <vector>
#include <string>
#include "WeatherData.h"

class TemperaturePredictor {
public:
    // Predict yearly temperature changes based on historical data
    std::vector<WeatherData> predictYearlyTemperatureChanges(const std::vector<WeatherData>& historicalData, int startYear, int numberOfYears);

private:
    // Helper function to calculate moving average
    float calculateMovingAverage(const std::vector<float>& data, int period);
};

#endif // TEMPERATUREPREDICTOR_H
