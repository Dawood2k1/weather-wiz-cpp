#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include <string>
#include "WeatherData.h"         // Custom header for WeatherData class
#include "Candlestick.h"         // Custom header for Candlestick class
#include "CandlestickChart.h"    // Custom header for candlestick chart plotting
#include "graphplot.h"           // Custom header for general graph plotting
#include "TemperaturePredictor.h"// Custom header for TemperaturePredictor class

// Function to display the welcome message
void displayWelcomeMessage() {
    std::cout << R"(
     /\__\         /\  \         /\  \         /\  \         /\__\         /\  \         /\  \                           /\__\          ___        /\  \
    /:/ _/_       /::\  \       /::\  \        \:\  \       /:/  /        /::\  \       /::\  \                         /:/  /         /\  \       \:\  \
   /:/ /\__\     /:/\:\  \     /:/\:\  \        \:\  \     /:/__/        /:/\:\  \     /:/\:\  \                       /:/  /          \:\  \       \:\  \
  /:/ /:/ _/_   /::\~\:\  \   /::\~\:\  \       /::\  \   /::\  \ ___   /::\~\:\  \   /::\~\:\  \                     /:/__/  ___      /::\__\       \:\  \
 /:/_/:/ /\__\ /:/\:\ \:\__\ /:/\:\ \:\__\     /:/\:\__\ /:/\:\  /\__\ /:/\:\ \:\__\ /:/\:\ \:\__\                    |:|  | /\__\  __/:/\/__/ _______\:\__\
 \:\/:/ /:/  / \:\~\:\ \/__/ \/__\:\/:/  /    /:/  \/__/ \/__\:\/:/  / \:\~\:\ \/__/ \/_|::\/:/  /                    |:|  |/:/  / /\/:/  /    \::::::::/__/
  \::/_/:/  /   \:\ \:\__\        \::/  /     \/__/            \::/  /   \:\ \:\__\      |:|\/__/                       \::::/__/    \:\__\       \:\  \
   \:\/:/  /     \:\ \/__/        /:/  /                      /:/  /     \:\ \/__/      |:|  |                          ~~~~         \/__/        \:\__\
    \::/  /       \:\__\         /:/  /                       \/__/         \/__/         \|__|                                                     \/__/
)";
    std::cout << std::endl;
}

// Function to display the main menu
void displayMenu() {
    std::cout << "    ________________________________________________________________________    \n";
    std::cout << "   /                                                                        \\  \n";
    std::cout << "  |                          Welcome to Weather Wiz!                         |  \n";
    std::cout << "  |                       Choose an option to get started:                   |  \n";
    std::cout << "  |__________________________________________________________________________|  \n";
    std::cout << "  |                                                                          |  \n";
    std::cout << "  |                      1. DISPLAY CANDLESTICK DATA                         |  \n";
    std::cout << "  |                      2. DISPLAY CANDLESTICK PLOT                         |  \n";
    std::cout << "  |                      3. FILTERED DATA PLOT                               |  \n";
    std::cout << "  |                      4. YEARLY TEMPERATURE PREDICTION DATA               |  \n";
    std::cout << "  |                      5. Exit (GOODBYE ! )                                |  \n";
    std::cout << "  |                                                                          |  \n";
    std::cout << "  \\_________________________________________________________________________ /  \n";
}


// Function prototype for displaying predicted temperatures
void displayPredictedTemperatures(const std::vector<WeatherData>& data);

int main() {
    // path to csv file please make sure to have actual path when you try to compile and execute it
    const std::string CSV_FILENAME = "/Users/muhammaddawood/Desktop/temp mid term  copy 6/src/weather_data.csv";

    std::string country_code;
    //vector to hold candlestick data
    std::vector<Candlestick> candlesticks;
    // flag to control the program loop
    bool shouldExit = false;

    // function usage to display the message
    displayWelcomeMessage();

    // main proogram loop
    while (!shouldExit) {
        // displays all the options to interact with the program
        displayMenu();
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
            case 2: {
                // Reset candlesticks vector for new data
                candlesticks.clear();
                std::cout << "Enter country code (e.g., GB, FR, ES): ";
                std::cin >> country_code;
                std::cout << "Enter year (1980-2019): ";
                int year;
                std::cin >> year;

                // Read CSV data based on country code
                auto data = readCSV(CSV_FILENAME, country_code);
                if (data.empty()) {
                    std::cerr << "No data found for country code: " << country_code << std::endl;
                    break;
                }
                // Handle case where no data is found for the country code
                // Filter data by the specified year
                auto filtered_data = filterDataByYear(data, year);
                if (filtered_data.empty()) {
                    std::cerr << "No data found for year: " << year << std::endl;
                    break;
                }
                // Compute monthly candlestick data from filtered data
                candlesticks = computeMonthlyCandlestickData(filtered_data);


                if (candlesticks.empty()) {
                    std::cerr << "No candlestick data computed." << std::endl;
                    break;
                }

                if (choice == 1) {
                    // Show candlestick data
                    displayCandlestickData(candlesticks);
                } else if (choice == 2) {
                    // Show candlestick plot
                    printCandlestickChart(candlesticks);
                }
                break;
            }
            case 3: {
                // Show temperature graph
                std::cout << "Enter country code (e.g., GB, FR, ES): ";
                std::cin >> country_code;
                // Depending on granularity, prompt for corresponding period input
                std::cout << "Choose data granularity (daily, monthly, yearly): ";
                std::string periodType;
                std::cin >> periodType;

                std::string period;
                if (periodType == "daily") {
                    std::cout << "Enter date (YYYY-MM-DD): ";
                    std::cin >> period;
                } else if (periodType == "monthly") {
                    std::cout << "Enter month (YYYY-MM): ";
                    std::cin >> period;
                } else if (periodType == "yearly") {
                    std::cout << "Enter year (YYYY): ";
                    std::cin >> period;
                } else {
                    std::cerr << "Invalid granularity choice." << std::endl;
                    break;
                }
                // Read CSV data based on country code
                auto data = readCSV(CSV_FILENAME, country_code);
                if (data.empty()) {
                    std::cerr << "No data found for country code: " << country_code << std::endl;
                    break;
                }
                // Display temperature graph based on user input
                displayTemperatureGraph(data, periodType, period);
                break;
            }
            case 4: {
                // Predict temperature changes
                std::cout << "Enter country code (e.g., GB, FR, ES): ";
                std::cin >> country_code;
                std::cout << "Enter start year (2020-2035): ";
                int startYear;
                std::cin >> startYear;
                if (startYear < 2020 || startYear > 2035) {
                    std::cerr << "Invalid start year. Please enter a year between 2020 and 2035." << std::endl;
                    break;
                }
                std::cout << "Enter number of years for prediction (up to 15 years): ";
                int numberOfYears;
                std::cin >> numberOfYears;
                if (numberOfYears < 1 || numberOfYears > 15) {
                    std::cerr << "Invalid number of years. Please enter a number between 1 and 15." << std::endl;
                    break;
                }

                auto data = readCSV(CSV_FILENAME, country_code);
                if (data.empty()) {
                    std::cerr << "No data found for country code: " << country_code << std::endl;
                    break;
                }

                TemperaturePredictor predictor;
                try {
                    auto predictedData = predictor.predictYearlyTemperatureChanges(data, startYear, numberOfYears);
                    displayPredictedTemperatures(predictedData);
                } catch (const std::exception& e) {
                    std::cerr << "Error predicting temperature changes: " << e.what() << std::endl;
                }
                break;
            }
            case 5:
                shouldExit = true;
                break;
            default:
                std::cerr << "Invalid choice. Please enter a valid option." << std::endl;
                // Clear error flags and flush input buffer
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
    }

    std::cout << "Exiting program. Thank you!\n";

    return 0;
}

//  function to display predicted temperatures data
void displayPredictedTemperatures(const std::vector<WeatherData>& data) {
    if (data.empty()) {
        std::cerr << "No data to display." << std::endl;
        return;
    }

    std::cout << "\nPredicted Yearly Temperatures:\n";
    std::cout << "Year      Temperature\n";
    std::cout << "----------------------\n";
    for (const auto& entry : data) {
        std::cout << entry.timestamp.substr(0, 4) << "   " << std::fixed << std::setprecision(2) << entry.temperature << "°C\n";
    }
}