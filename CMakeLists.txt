cmake_minimum_required(VERSION 3.30)
project(tp_calculator)

# Set C++ standard and enable AUTOMOC, AUTORCC, AUTOUIC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/views)

# Find Qt6 components
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

# Include directories
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/ui
        ${CMAKE_CURRENT_SOURCE_DIR}/logic
        ${CMAKE_CURRENT_SOURCE_DIR}/views
)

# Define source files
set(SOURCES
        main.cpp
        ui/main_window.cpp
        logic/calculator_engine.cpp
        views/main_window.ui
)

# Group files visually in IDEs
source_group("views" FILES views/main_window.ui)

# Create the executable
add_executable(tp_calculator ${SOURCES})

# Link Qt libraries
target_link_libraries(tp_calculator
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
