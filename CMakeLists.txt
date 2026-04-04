cmake_minimum_required(VERSION 4.0.0)

project(game01 LANGUAGES CXX)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
add_compile_definitions(SFML_STATIC)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

include(FetchContent)

# SFML 3.0.2 (STATIC)
#============================================================================
set(SFML_STATIC_LIBRARIES ON)
set(BUILD_SHARED_LIBS OFF)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_TESTS OFF)
set(SFML_BUILD_DOC OFF)
set(SFML_VERSION 3.0.2)


FetchContent_Declare(
    SFML
    URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
)
FetchContent_MakeAvailable(SFML)
# #============================================================================
# # ImGui (STATIC)
# #============================================================================
set(IMGUI_VERSION 1.91.1)
FetchContent_Declare(
    imgui
    URL "https://github.com/ocornut/imgui/archive/v${IMGUI_VERSION}.zip"
)
FetchContent_MakeAvailable(imgui)

#============================================================================
# ImGui-SFML (STATIC) — manual build, bypass CMakeLists.txt
#============================================================================
set(IMGUI_SFML_VERSION 3.0)
FetchContent_Declare(
    imgui_sfml
    URL "https://github.com/SFML/imgui-sfml/archive/v${IMGUI_SFML_VERSION}.zip"
)
set(IMGUI_DIR ${imgui_SOURCE_DIR} CACHE PATH "" FORCE)
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(imgui_sfml)

#============================================================================
# Game project
#============================================================================
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

add_library(game_logic STATIC ${SOURCES})
target_include_directories(game_logic PUBLIC ${INCLUDE_DIR})
target_link_libraries(game_logic PUBLIC
    ImGui-SFML::ImGui-SFML
)
add_executable(${PROJECT_NAME} Main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    game_logic 
    ImGui-SFML::ImGui-SFML
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32 glu32 winmm gdi32)
endif()

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

enable_testing()
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
    add_subdirectory(tests)
endif()