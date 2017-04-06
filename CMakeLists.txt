cmake_minimum_required(VERSION 3.5)

set(MODE "platform" CACHE STRING "")
set(ARDUINO_CXX_FLAGS "-std=c++14 -mcall-prologues -ffunction-sections -fdata-sections -fno-exceptions")

if (${MODE} STREQUAL "platform")
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/../arduino-cmake/cmake/ArduinoToolchain.cmake)
endif (${MODE} STREQUAL "platform")

Project(avr-core)

if (${MODE} STREQUAL "unit")
    enable_testing()
    include(CTest)
    add_subdirectory(test)
elseif(${MODE} STREQUAL "platform")
    add_subdirectory(platform_test)
endif (${MODE} STREQUAL "unit")
