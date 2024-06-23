cmake_minimum_required(VERSION 3.20)
project(kaio VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)  # Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Make the C++ standard required

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${${PROJECT_NAME}_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${${PROJECT_NAME}_BINARY_DIR}/bin")

if(WIN32)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
endif()

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${CMAKE_CURRENT_SOURCE_DIR}/build")

add_library(${PROJECT_NAME})

# find packages
find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_ttf REQUIRED CONFIG)
find_package(SDL2_IMAGE REQUIRED CONFIG)
find_package(glm REQUIRED CONFIG)

add_subdirectory(source) 

add_subdirectory(extern) 

if(EMSCRIPTEN)
    set(EXECUTABLE_NAME "index")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -DEMCC_DEBUG=2 -g4") #--preload-file=gba4.png")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
else()
    set(EXECUTABLE_NAME "main")
endif()

if(EMSCRIPTEN)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 SDL2_image SDL2_ttf)
else()
# SDL2
    find_package(SDL2 REQUIRED CONFIG)
    find_package(SDL2_ttf REQUIRED CONFIG)
    find_package(SDL2_IMAGE REQUIRED CONFIG)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
    if(TARGET SDL2::SDL2-static)
        target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2-static)
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)
    endif()

    if(TARGET SDL2_ttf::SDL2_ttf)
        target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_ttf::SDL2_ttf)
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_ttf::SDL2_ttf-static)
    endif()

    if(TARGET SDL2_image::SDL2_image-static)
        target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image-static)
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image)
    endif()
endif()


# glm
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

# Enable imgui default math operator
add_compile_definitions(IMGUI_DEFINE_MATH_OPERATORS)

# staging -- these are test executables to run
option(BUILD_STAGING "Build staging" ON)
if(BUILD_STAGING)
    add_subdirectory(staging) 
endif()

# examples -- fully fletched out examples
option(BUILD_EXAMPLES "Build examples" OFF)
if(BUILD_EXAMPLES)
    add_subdirectory(examples) 
endif()

file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)
