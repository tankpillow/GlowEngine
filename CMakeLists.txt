cmake_minimum_required(VERSION 3.25)
project(GlowEngine LANGUAGES CXX)

# --- Compile Commands Settings --- #
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(COMPILE_COMMANDS_TOP ${CMAKE_SOURCE_DIR}/compile_commands.json)

add_custom_target(export_compile_commands_top ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${COMPILE_COMMANDS_TOP}
    COMMENT "Exporting compile_commands.json to top level"
    VERBATIM
)

# --- Configure C++ --- #
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Configure Output Directory --- #
string(TOLOWER "${PLATFORM}" PLATFORM_DIR)
string(TOLOWER "${CMAKE_BUILD_TYPE}" BUILD_TYPE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PLATFORM_DIR}-${BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PLATFORM_DIR}-${BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PLATFORM_DIR}-${BUILD_TYPE})

if (MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif()

# --- Fetch Raylib --- #
include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "6.0"
)
    
message(STATUS "Fetching raylib...")
FetchContent_MakeAvailable(raylib)

message(STATUS "Compiling ImGui")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)

# -- Add Executable -- #
file(GLOB_RECURSE SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

# -- Include Directories & Link Libraries -- #
target_include_directories(${PROJECT_NAME} 
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/"
)

target_link_libraries(${PROJECT_NAME} 
    raylib
    imgui
)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()