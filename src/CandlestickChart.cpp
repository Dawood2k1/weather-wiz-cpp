#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
#include "CandlestickChart.h"

void printCandlestickChart(const std::vector<Candlestick>& candlesticks) {
    if (candlesticks.empty()) {
        std::cerr << "No data to plot." << std::endl;
        return;
    }

    double minVal = std::numeric_limits<double>::max();
    double maxVal = std::numeric_limits<double>::lowest();

    // Determine the overall min and max values for the year
    for (const auto& candle : candlesticks) {
        minVal = std::min(minVal, static_cast<double>(candle.low));
        maxVal = std::max(maxVal, static_cast<double>(candle.high));
    }

    // Ensure minVal and maxVal are not equal to avoid division by zero
    if (minVal == maxVal) {
        minVal -= 1.0; // Adjust minVal slightly if equal
    }

    int height = 20; // Number of rows for the plot height
    int width = candlesticks.size() * 7; // Number of columns for the plot width (7 characters per candlestick)

    // Scaling factor to map temperature values to the plot height
    double scale = height / (maxVal - minVal);

    std::vector<std::string> plot(height, std::string(width, ' ')); // Each column initialized with spaces

    for (int i = 0; i < candlesticks.size(); ++i) {
        const auto& candle = candlesticks[i];

        int openPos = static_cast<int>((candle.open - minVal) * scale);
        int closePos = static_cast<int>((candle.close - minVal) * scale);
        int highPos = static_cast<int>((candle.high - minVal) * scale);
        int lowPos = static_cast<int>((candle.low - minVal) * scale);

        int col = i * 7; // Each candlestick starts at col = i * 7

        // Plot the high-low range
        for (int j = std::max(0, std::min(lowPos, highPos)); j <= std::min(height - 1, std::max(lowPos, highPos)); ++j) {
            plot[j][col + 3] = '|';
        }

        // Plot the candlestick body
        for (int j = std::max(0, std::min(openPos, closePos)); j <= std::min(height - 1, std::max(openPos, closePos)); ++j) {
            if (openPos > closePos) {
                plot[j][col + 2] = '|';
                plot[j][col + 3] = '_';
                plot[j][col + 4] = '|';
            } else {
                plot[j][col + 2] = '|';
                plot[j][col + 3] = ' ';
                plot[j][col + 4] = '|';
            }
        }

        // Top and bottom of the candlestick
        if (openPos > closePos) {
            if (openPos < height) plot[openPos][col + 3] = '_';
            if (closePos < height) plot[closePos][col + 3] = '_';
        } else {
            if (openPos < height) plot[openPos][col + 3] = ' ';
            if (closePos < height) plot[closePos][col + 3] = ' ';
        }
    }

    // Print the plot
    for (int i = 0; i < height; ++i) {
        std::cout << std::setw(6) << std::fixed << std::setprecision(1) << (maxVal - i * (maxVal - minVal) / height) << " |";
        std::cout << plot[i] << std::endl;
    }

    // Print the month labels
    std::cout << "      ";
    for (int i = 1; i <= 12; ++i) {
        std::cout << std::setw(7) << std::setfill(' ') << std::right << i;
    }
    std::cout << std::endl;

    // Print the key
    std::cout << "Key:\n";
    std::cout << "|___| : open > close (bearish candle)\n";
    std::cout << "|   | : open < close (bullish candle)\n";
    std::cout << "|   | : high to low range\n";
}
