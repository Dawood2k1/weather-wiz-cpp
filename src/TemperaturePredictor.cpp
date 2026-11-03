#include "TemperaturePredictor.h"
#include <algorithm>
#include <numeric>
#include <stdexcept>

float TemperaturePredictor::calculateMovingAverage(const std::vector<float>& data, int period) {
    if (data.size() < period) throw std::invalid_argument("Data size is less than the period");

    float sum = std::accumulate(data.end() - period, data.end(), 0.0f);
    return sum / period;
}

std::vector<WeatherData> TemperaturePredictor::predictYearlyTemperatureChanges(const std::vector<WeatherData>& historicalData, int startYear, int numberOfYears) {
    std::vector<WeatherData> predictions;
    std::vector<float> temperatures;

    // Extract temperatures from the historical data
    for (const auto& entry : historicalData) {
        temperatures.push_back(entry.temperature);
    }

    if (temperatures.empty()) throw std::runtime_error("No historical temperature data available");

    const int period = 5; // Using a 5-year moving average for predictions
    for (int year = startYear; year < startYear + numberOfYears; ++year) {
        float predictedTemp = calculateMovingAverage(temperatures, period);
        predictions.push_back({std::to_string(year) + "-01-01", predictedTemp});
        temperatures.push_back(predictedTemp); // Use the predicted temperature for future predictions
    }

    return predictions;
}
