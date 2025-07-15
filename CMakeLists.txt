cmake_minimum_required(VERSION 3.5)
project(VisualCalculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets QUIET)
if(Qt5_FOUND)
    set(QtPackage Qt5)
else()
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QtPackage Qt6)
endif()

add_executable(calculator
    src/main.cpp
    src/Calculator.cpp
    src/Calculator.h
)

target_link_libraries(calculator ${QtPackage}::Widgets)

