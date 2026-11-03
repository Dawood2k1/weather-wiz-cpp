# Weather Wiz

A command-line C++ program that turns 40 years of European temperature records into candlestick charts and simple forecasts. Built for the Object-Oriented Programming module of my University of London BSc Computer Science.

## What it does

Pick a country by its code (GB, FR, ES and so on), then choose from the menu:

1. **Candlestick data:** the open, high, low and close temperature for each month of a chosen year (1980–2019), each month labelled bullish, bearish or doji.
2. **Candlestick plot:** the same months drawn as a text candlestick chart in the terminal.
3. **Filtered data plot:** a temperature graph for one day, one month or one year.
4. **Yearly prediction:** projects temperatures forward a year at a time with a moving average of the last five values, feeding each prediction back in.

## Design

| Class / file | Responsibility |
| --- | --- |
| `WeatherData` | Reads the CSV, finds the chosen country's temperature column, and filters records by year, month or day |
| `Candlestick` | One period's open, high, low and close |
| `CandlestickChart` | Draws candlesticks in the terminal |
| `graphplot` | Draws filtered temperature graphs |
| `TemperaturePredictor` | Moving-average forecasting |
| `main.cpp` | The menu and user input |

## Build and run

Requires CMake 3.28+ and a C++17 compiler.

```bash
cmake -S . -B build
cmake --build build
./build/temp_mid_term_
```

The program reads hourly temperatures from a CSV in the [Open Power System Data weather dataset](https://data.open-power-system-data.org/weather_data/) format: a `utc_timestamp` column followed by `<COUNTRY>_temperature` columns. The dataset isn't included here. Download it and set `CSV_FILENAME` in `src/main.cpp` to its path.
