cmake_minimum_required(VERSION 3.28)
project(temp_mid_term_)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(temp_mid_term_
        src/Candlestick.cpp
        src/Candlestick.h
        src/main.cpp
        src/WeatherData.cpp
        src/WeatherData.h
        src/CandlestickChart.cpp
        src/CandlestickChart.h
        src/graphplot.cpp
        src/graphplot.h
        src/graphplot.cpp
        src/TemperaturePredictor.cpp
        src/TemperaturePredictor.h
)
