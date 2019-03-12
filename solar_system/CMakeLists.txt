cmake_minimum_required(VERSION 3.6)
project( SolarSystem )

set(CMAKE_CXX_FLAGS_RELEASE "-O1 -g0 -Werror -std=c++11 -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -Wall -std=c++11 -pthread")

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

include_directories(include)
link_directories(${PROJECT_SOURCE_DIR}/include/lib-vc2015)
link_directories(${PROJECT_SOURCE_DIR}/include/lib-mingw)

set(WINDOW_SOURCES
        ${PROJECT_SOURCE_DIR}/src/window/Window.cpp
        ${PROJECT_SOURCE_DIR}/src/window/Window.h
        ${PROJECT_SOURCE_DIR}/src/window/Color.h
        )

set(PHYSICSOBJECT_SOURCES
        ${PROJECT_SOURCE_DIR}/src/physics_object/Vector2.h
        ${PROJECT_SOURCE_DIR}/src/physics_object/Vector2Int.h
        ${PROJECT_SOURCE_DIR}/src/physics_object/GravityObject.cpp
        ${PROJECT_SOURCE_DIR}/src/physics_object/GravityObject.h
        ${PROJECT_SOURCE_DIR}/src/physics_object/PhysicsObject.cpp
        ${PROJECT_SOURCE_DIR}/src/physics_object/PhysicsObject.h
        ${PROJECT_SOURCE_DIR}/src/physics_object/ObjectData.cpp
        ${PROJECT_SOURCE_DIR}/src/physics_object/ObjectData.h
        )

set(TIMEKEEPING_SOURCES
        ${PROJECT_SOURCE_DIR}/src/time_keeping/Timer.h
        src/window/Color.h
        )

add_executable(SolarSystem
        src/solar_system_simulator.cpp
        ${WINDOW_SOURCES}
        ${PHYSICSOBJECT_SOURCES}
        ${TIMEKEEPING_SOURCES}
        )

include_directories(SolarSystem ${OPENGL_INCLUDE_DIR})

target_link_libraries(SolarSystem
        ${OPENGL_gl_LIBRARY}
        glfw3dll
        pthread
        ${CMAKE_THREAD_LIBS_INIT})
