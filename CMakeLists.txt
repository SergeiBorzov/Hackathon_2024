cmake_minimum_required(VERSION 3.20)
project(Hackathon VERSION 0.1.0 LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Fetch SFML from github
include(FetchContent)
FetchContent_Declare(
    sfmllib
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
)
FetchContent_MakeAvailable(sfmllib)

# Put compiled binaries inside 'bin'
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Create an executable. It has only one source file to start with.
add_executable(${PROJECT_NAME} main.cpp)

# Let's use the latest C++ standard (if your compiler can't support it, you can just lower to 20, 17, 14, 11, whatever works)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

# Link in the SFML libraries to the executable
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-audio sfml-graphics sfml-system sfml-window)

# Make it a bit cleaner to load assets in the code by defining ASSETS to point to the assets folder
target_compile_definitions(${PROJECT_NAME} PRIVATE ASSETS="${CMAKE_CURRENT_SOURCE_DIR}/assets")

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()