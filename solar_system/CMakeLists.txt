cmake_minimum_required(VERSION 2.8)
project( SolarSystem )
find_package( OpenCV 3 REQUIRED )

SET(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-O0 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")


set(WINDOW_SOURCES
        ${PROJECT_SOURCE_DIR}/src/window/Window.cpp
        ${PROJECT_SOURCE_DIR}/src/window/Window.h
        ${PROJECT_SOURCE_DIR}/src/window/Drawer.cpp
        ${PROJECT_SOURCE_DIR}/src/window/Drawer.h
        )

set(PLANETARYBODY_SOURCES
        ${PROJECT_SOURCE_DIR}/src/planetary_body/PlanetaryBody.h
        )


include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(SolarSystem
        src/solar_system_simulator.cpp
        ${WINDOW_SOURCES}
        ${PLANETARYBODY_SOURCES}
        )

target_link_libraries( SolarSystem ${OpenCV_LIBS} )