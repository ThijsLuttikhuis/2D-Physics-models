cmake_minimum_required(VERSION 2.8)
project( SolarSystem )
find_package( OpenCV 3 REQUIRED )

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-O0 -Wall -Wextra -std=c++11 -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -std=c++11 -pthread")

find_package(Threads REQUIRED)

set(WINDOW_SOURCES
        ${PROJECT_SOURCE_DIR}/src/window/Window.cpp
        ${PROJECT_SOURCE_DIR}/src/window/Window.h
        ${PROJECT_SOURCE_DIR}/src/window/Drawer.cpp
        ${PROJECT_SOURCE_DIR}/src/window/Drawer.h
        )

set(PLANETARYBODY_SOURCES
        ${PROJECT_SOURCE_DIR}/src/planetary_body/PlanetaryBody.h
        ${PROJECT_SOURCE_DIR}/src/planetary_body/PlanetData.h
        ${PROJECT_SOURCE_DIR}/src/planetary_body/PlanetData.cpp
        )

set(TIMEKEEPING_SOURCES
        ${PROJECT_SOURCE_DIR}/src/time_keeping/Timer.h
        )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(SolarSystem
        src/solar_system_simulator.cpp
        ${WINDOW_SOURCES}
        ${PLANETARYBODY_SOURCES}
        ${TIMEKEEPING_SOURCES}
        )

add_definitions(-std=c++0x -O3) # -m64)

TARGET_LINK_LIBRARIES(
        SolarSystem
        ${OpenCV_LIBS}
        pthread
        X11
        ${CMAKE_THREAD_LIBS_INIT}
        ${OpenCV_LIBRARIES}
        )