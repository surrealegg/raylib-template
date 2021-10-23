# Make sure that your cmake minimmum version is 3.7.2
cmake_minimum_required(VERSION 3.7.2)

# Change your project name and version here.
project(raylib-template VERSION 1.0)

# Handle error "Policy CMP0074 is not set".
if (POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW)
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Default build type is Release with Debug information
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

# Use C11 and C++14 and enforce it
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(raylib 3.0 REQUIRED)

# There's an issue where VCPKG has different variables for raylib
# https://github.com/microsoft/vcpkg/blob/030cfaa24de9ea1bbf0a4d9c615ce7312ba77af1/ports/raylib/vcpkg-cmake-wrapper.cmake#L10
if (MSVC)
    if(NOT DEFINED ${raylib_INCLUDE_DIRS})
        set(raylib_INCLUDE_DIRS ${RAYLIB_INCLUDE_DIRS})
    endif()

    if(NOT DEFINED ${raylib_LIBRARIES})
        set(raylib_LIBRARIES ${RAYLIB_LIBRARIES})
    endif()
endif()

# Add Additional flags for the Web
if (EMSCRIPTEN)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

# Copy all assets to binary directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

# Create a execuable.
# Add your new files here.
add_executable(${PROJECT_NAME} src/main.c)

# Add Raylib include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${raylib_INCLUDE_DIRS})

# Link Raylib libaries
target_link_libraries(${PROJECT_NAME} PRIVATE ${raylib_LIBRARIES})

# Add Additional flags for MacOS
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
