#include "graphplot.h"
#include "WeatherData.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <limits>

void displayTemperatureGraph(const std::vector<WeatherData>& data, const std::string& periodType, const std::string& period) {
    if (data.empty()) {
        std::cerr << "No data to plot." << std::endl;
        return;
    }

    std::vector<WeatherData> filtered_data;
    std::string x_axis_label;

    if (periodType == "daily") {
        x_axis_label = "Hour";
        std::map<int, float> hour_avg_temperatures;
        std::map<int, int> hour_count;

        for (const auto& entry : data) {
            if (entry.timestamp.substr(0, 10) == period) {
                int hour = std::stoi(entry.timestamp.substr(11, 2));
                hour_avg_temperatures[hour] += entry.temperature;
                hour_count[hour]++;
            }
        }

        for (const auto& [hour, total_temp] : hour_avg_temperatures) {
            float avg_temp = total_temp / hour_count[hour];
            filtered_data.push_back({ (hour < 10 ? "0" : "") + std::to_string(hour), avg_temp });
        }
    } else if (periodType == "monthly") {
        x_axis_label = "Day";
        std::map<int, float> day_avg_temperatures;
        std::map<int, int> day_count;

        for (const auto& entry : data) {
            if (entry.timestamp.substr(0, 7) == period) {
                int day = std::stoi(entry.timestamp.substr(8, 2));
                day_avg_temperatures[day] += entry.temperature;
                day_count[day]++;
            }
        }

        for (const auto& [day, total_temp] : day_avg_temperatures) {
            float avg_temp = total_temp / day_count[day];
            filtered_data.push_back({ (day < 10 ? "0" : "") + std::to_string(day), avg_temp });
        }
    } else if (periodType == "yearly") {
        x_axis_label = "Month";
        std::map<int, float> month_avg_temperatures;
        std::map<int, int> month_count;

        for (const auto& entry : data) {
            if (entry.timestamp.substr(0, 4) == period) {
                int month = std::stoi(entry.timestamp.substr(5, 2));
                month_avg_temperatures[month] += entry.temperature;
                month_count[month]++;
            }
        }

        for (const auto& [month, total_temp] : month_avg_temperatures) {
            float avg_temp = total_temp / month_count[month];
            filtered_data.push_back({ (month < 10 ? "0" : "") + std::to_string(month), avg_temp });
        }
    }

    if (filtered_data.empty()) {
        std::cerr << "No data found for the specified filters." << std::endl;
        return;
    }

    // Find min and max temperatures for scaling
    float min_temp = std::numeric_limits<float>::max();
    float max_temp = std::numeric_limits<float>::min();
    for (const auto& entry : filtered_data) {
        if (entry.temperature < min_temp) {
            min_temp = entry.temperature;
        }
        if (entry.temperature > max_temp) {
            max_temp = entry.temperature;
        }
    }

    // Define graph dimensions and padding
    const int graph_height = 30;
    const int x_spacing = 3; // Use an integer value for spacing
    int graph_width = filtered_data.size() * x_spacing;

    // Calculate temperature range and interval for y-axis scaling
    float temp_range = max_temp - min_temp;
    float temp_interval = temp_range / graph_height;

    // Initialize a 2D vector for the graph
    std::vector<std::vector<char>> graph(graph_height, std::vector<char>(graph_width, ' '));

    // Plot the data points
    for (size_t x = 0; x < filtered_data.size(); ++x) {
        int y = static_cast<int>((filtered_data[x].temperature - min_temp) / temp_interval);
        if (y >= graph_height) y = graph_height - 1;
        graph[graph_height - y - 1][x * x_spacing] = '*';  // x * x_spacing to add space between points
    }

    // Print temperature graph
    std::cout << "Temperature Graph:\n";

    // Print y-axis labels and graph rows
    for (int i = graph_height - 1; i >= 0; --i) {
        float temp_value = min_temp + i * temp_interval;
        std::cout << std::setw(5) << std::fixed << std::setprecision(1) << temp_value << " | ";
        for (int j = 0; j < graph_width; ++j) {
            std::cout << graph[i][j];
        }
        std::cout << "\n";
    }

    // Print x-axis dynamically based on label width
    std::cout << std::setw(5) << " " << " +";
    for (int i = 0; i < graph_width; ++i) {
        std::cout << "-";
    }
    std::cout << "> " << x_axis_label << "\n";

    // Print x-axis labels
    std::cout << std::setw(6) << " ";
    for (size_t x = 0; x < filtered_data.size(); ++x) {
        std::cout << std::setw(x_spacing) << std::setfill(' ') << filtered_data[x].timestamp;
    }
    std::cout << "\n";
}
