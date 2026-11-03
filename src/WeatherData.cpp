#include "WeatherData.h"
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <iostream>

std::vector<WeatherData> readCSV(const std::string& filename, const std::string& country_code) {
    std::vector<WeatherData> data;
    std::ifstream file(filename);
    std::string line, cell;

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return data;
    }

    // Read header to find the index of the required country's temperature column
    std::getline(file, line);
    std::istringstream header_stream(line);
    std::vector<std::string> headers;
    while (std::getline(header_stream, cell, ',')) {
        headers.push_back(cell);
    }

    int temp_col = -1;
    for (int i = 0; i < headers.size(); ++i) {
        if (headers[i] == country_code + "_temperature") {
            temp_col = i;
            break;
        }
    }

    if (temp_col == -1) {
        std::cerr << "Temperature column for " << country_code << " not found!" << std::endl;
        return data;
    }

    // Read data
    while (std::getline(file, line)) {
        std::istringstream line_stream(line);
        std::vector<std::string> row;
        while (std::getline(line_stream, cell, ',')) {
            row.push_back(cell);
        }

        if (row.size() > temp_col) {
            WeatherData wd;
            wd.timestamp = row[0];
            wd.temperature = std::stof(row[temp_col]);
            data.push_back(wd);
        }
    }

    file.close();
    return data;
}

std::vector<WeatherData> filterDataByYear(const std::vector<WeatherData>& data, int year) {
    std::vector<WeatherData> filtered_data;
    std::string year_str = std::to_string(year);

    for (const auto& entry : data) {
        if (entry.timestamp.substr(0, 4) == year_str) {
            filtered_data.push_back(entry);
        }
    }

    return filtered_data;
}

std::vector<Candlestick> computeMonthlyCandlestickData(const std::vector<WeatherData>& data) {
    std::map<std::string, std::vector<float>> monthly_data;

    // Organize data by month
    for (const auto& entry : data) {
        std::string month = entry.timestamp.substr(0, 7); // YYYY-MM
        monthly_data[month].push_back(entry.temperature);
    }

    // Compute candlestick data for each month
    std::vector<Candlestick> candlesticks;
    for (const auto& [month, temps] : monthly_data) {
        if (!temps.empty()) {
            float open = temps.front();
            float close = temps.back();
            float high = *std::max_element(temps.begin(), temps.end());
            float low = *std::min_element(temps.begin(), temps.end());

            candlesticks.emplace_back(month, open, high, low, close);
        }
    }

    return candlesticks;
}
