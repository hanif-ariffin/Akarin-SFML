cmake_minimum_required(VERSION 3.10.2)
project(stardust)

set(EXECUTABLE_NAME "${CMAKE_PROJECT_NAME}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wpedantic")

message(STATUS ${CMAKE_BUILD_TYPE})
message(CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR})

# Define sources and executable.
file(GLOB_RECURSE SOURCE_FILES
        "include/*.h"
        "src/*.cpp"
        )

include_directories("./Include")
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
# SFML #
find_package(SFML 2 COMPONENTS graphics window audio system REQUIRED)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()