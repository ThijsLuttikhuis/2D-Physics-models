cmake_minimum_required(VERSION 3.6)
project( SolarSystem )

set(CMAKE_CXX_FLAGS_RELEASE "-O1 -g0 -Werror -std=c++11 -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -Wall -Wextra -std=c++11 -pthread")

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

include_directories(include)
link_directories(${PROJECT_SOURCE_DIR}/include/lib-vc2015)
link_directories(${PROJECT_SOURCE_DIR}/include/lib-mingw)

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
        src/window/Color.h src/planetary_body/Vector2.h src/planetary_body/Vector2Int.h src/planetary_body/PlanetaryBody.cpp)

add_executable(SolarSystem
        src/solar_system_simulator.cpp
        ${WINDOW_SOURCES}
        ${PLANETARYBODY_SOURCES}
        ${TIMEKEEPING_SOURCES}
        )

include_directories(SolarSystem ${OPENGL_INCLUDE_DIR})

target_link_libraries(SolarSystem
        ${OPENGL_gl_LIBRARY}
        glfw3dll
        pthread
        ${CMAKE_THREAD_LIBS_INIT})
