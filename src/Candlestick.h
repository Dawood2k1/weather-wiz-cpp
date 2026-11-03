#ifndef CANDLESTICK_H  // Header guard to prevent multiple inclusions
#define CANDLESTICK_H

#include <string>
#include <vector>

// Definition of the Candlestick class
class Candlestick {
public:
    std::string date; // Date of the candlestick in format YYYY-MM-DD
    float open;       // Opening price of the candlestick
    float high;       // Highest price during the candlestick period
    float low;        // Lowest price during the candlestick period
    float close;      // Closing price of the candlestick

    // Constructor for initializing a Candlestick object
    Candlestick(std::string date, float open, float high, float low, float close);
};

// Function prototype for displaying candlestick data
void displayCandlestickData(const std::vector<Candlestick>& candlesticks);

#endif // CANDLESTICK_H
