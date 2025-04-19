cmake_minimum_required(VERSION 3.30)
project(tp_calculator VERSION 1.0.0)

# Set C++ standard and enable AUTOMOC, AUTORCC, AUTOUIC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_MACOSX_BUNDLE ON)
set(APP_NAME "TP Calculator")
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
        ui/MainWindow.cpp
        ui/BasicPage.cpp
        ui/SettingsPage.cpp
        views/MainWindow.ui
        views/BasicPage.ui
        views/SettingsPage.ui
        logic/Settings.cpp
        logic/core/ExpressionParser.cpp
)

# Group files visually in IDEs
source_group("views" FILES views/MainWindow.ui views/BasicPage.ui views/SettingsPage.ui)

# Create the executable
add_executable(tp_calculator ${SOURCES})

if (APPLE)
    set_target_properties(tp_calculator PROPERTIES
            MACOSX_BUNDLE TRUE
            OUTPUT_NAME "${APP_NAME}"
            MACOSX_BUNDLE_BUNDLE_NAME "${APP_NAME}"
    )
else ()
    set_target_properties(tp_calculator PROPERTIES
            MACOSX_BUNDLE TRUE
            OUTPUT_NAME "${APP_NAME}"
            MACOSX_BUNDLE_BUNDLE_NAME "${APP_NAME}"
    )
endif ()

# Link Qt libraries
target_link_libraries(tp_calculator
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

include(InstallRequiredSystemLibraries)

if (WIN32)
    set(CPACK_GENERATOR "NSIS")
elseif (APPLE)
    set(CPACK_GENERATOR "DragNDrop")
else ()
    set(CPACK_GENERATOR "DEB")
endif ()

# Define the install target (install app binary)
if (APPLE)
    install(TARGETS tp_calculator BUNDLE DESTINATION .)
else ()
    install(TARGETS tp_calculator RUNTIME DESTINATION bin)
endif ()

set(CPACK_PACKAGE_NAME "${APP_NAME}")
set(CPACK_PACKAGE_VENDOR "Aleksey Demchenkov")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A simple Qt-based calculator as a term project.")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "pelfox@younunion.ru")

set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-Source")

# Include CPack module
include(CPack)
