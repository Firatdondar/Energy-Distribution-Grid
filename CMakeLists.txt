cmake_minimum_required(VERSION 3.10)
project(EnergyDistributionGrid)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(EnergyDistributionGrid src/main.cpp)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
