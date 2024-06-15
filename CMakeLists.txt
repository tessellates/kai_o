cmake_minimum_required(VERSION 3.20)
project(kaio VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)  # Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Make the C++ standard required

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${kaio_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${kaio_BINARY_DIR}/bin")

if(WIN32)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
endif()

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${CMAKE_CURRENT_SOURCE_DIR}/build")

add_executable(kaio source/main.cpp)

install(
    TARGETS kaio
    ARCHIVE
        DESTINATION run
    LIBRARY
        DESTINATION run
    RUNTIME
        DESTINATION run
    INCLUDES 
        DESTINATION run
)
