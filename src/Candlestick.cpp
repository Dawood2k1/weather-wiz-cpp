#include "Candlestick.h"  // Include header file for Candlestick class
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <utility>

// Constructor for Candlestick class
Candlestick::Candlestick(std::string date, float open, float high, float low, float close)
        : date(std::move(date)), open(open), high(high), low(low), close(close) {}

// Function to display candlestick data
void displayCandlestickData(const std::vector<Candlestick>& candlesticks) {
    // Header for the table
    std::cout << "+-----------------+--------------------------+\n";
    std::cout << "|     Date        |          Candlestick     |\n";
    std::cout << "+-----------------+--------------------------+\n";

    // Loop through each candlestick in the vector
    for (const auto& candle : candlesticks) {
        std::string candleType;

        // Determine if the candlestick is Bullish, Bearish, or a Doji
        if (candle.close > candle.open) {
            candleType = "Bullish";
        } else if (candle.close < candle.open) {
            candleType = "Bearish";
        } else {
            candleType = "Doji";
        }

        // Display candlestick data in a formatted table row
        std::cout << "| " << std::setw(15) << candle.date << " | ";
        std::cout << "Open: " << std::setw(6) << candle.open;
        std::cout << " Close: " << std::setw(6) << candle.close;
        std::cout << " High: " << std::setw(6) << candle.high;
        std::cout << " Low: " << std::setw(6) << candle.low;
        std::cout << " (" << candleType << ") ";
        std::cout << "|\n";

        // ASCII art representation of the candlestick
        std::cout << "|                 | ";
        if (candleType == "Bullish") {
            std::cout << "   |     \n";
            std::cout << "|                 |  \\ | /  \n";
            std::cout << "|                 |   \\|/   \n";
            std::cout << "|                 |    |    \n";
        } else if (candleType == "Bearish") {
            std::cout << "    |    \n";
            std::cout << "|                 |   /|\\   \n";
            std::cout << "|                 |  / | \\  \n";
            std::cout << "|                 |    |    \n";
        } else {
            std::cout << "    |    \n";
            std::cout << "|                 |   /|\\   \n";
            std::cout << "|                 |  \\ | /  \n";
            std::cout << "|                 |    |    \n";
        }

        // Footer of the table for each candlestick
        std::cout << "+-----------------+--------------------------+\n";
    }
}
