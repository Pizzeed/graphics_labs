cmake_minimum_required(VERSION 3.21)

message("${CMAKE_PREFIX_PATH}")

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  graphics_cw
  VERSION 0.0.1
  DESCRIPTION "Second task of the computer graphics course"
  LANGUAGES CXX)

file(CREATE_LINK
    "${CMAKE_BINARY_DIR}/compile_commands.json"
    "${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json"
    SYMBOLIC
)

file(COPY 
        "${CMAKE_CURRENT_SOURCE_DIR}/assets/" 
     DESTINATION 
        "${CMAKE_CURRENT_BINARY_DIR}/assets/"
)

find_package(labs_engine REQUIRED)
find_package(ImGui REQUIRED)
find_package(stb REQUIRED)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PUBLIC
PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/materials/colored_material.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/materials/textured_material.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/shapes/sphere.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/main.cc
  
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/bindings/imgui_impl_glfw.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/bindings/imgui_impl_opengl3.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
PUBLIC
  labs_engine::labs_engine
  stb::stb
  imgui::imgui
)

target_compile_definitions(${PROJECT_NAME}
PRIVATE
  CMAKE_BINARY_DIR="${CMAKE_BINARY_DIR}")