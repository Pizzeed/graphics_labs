cmake_minimum_required(VERSION 3.21)

message("${CMAKE_PREFIX_PATH}")

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  labs_engine
  VERSION 0.0.1
  DESCRIPTION "Simple graphical application engine for SPBPU computer graphics labs"
  LANGUAGES CXX)

file(CREATE_LINK
    "${CMAKE_BINARY_DIR}/compile_commands.json"
    "${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json"
    SYMBOLIC
)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(imgui REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME})
add_executable(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

include_directories( ${OPENGL_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME}
PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
  $<INSTALL_INTERFACE:include/>
PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/bindings/
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/
)

target_sources(${PROJECT_NAME}
PUBLIC
PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/main.cc

  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/utils/color.cc

  
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/application/application.cc
  
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/glad/glad.cc
  
  ${CMAKE_CURRENT_SOURCE_DIR}/bindings/imgui_impl_glfw.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/bindings/imgui_impl_opengl3.cpp

)
target_link_libraries(${PROJECT_NAME}
PRIVATE
  ${OPENGL_LIBRARIES}
  glfw
  glm::glm
  imgui::imgui
)

message(
  STATUS
    "[${PROJECT_NAME}] installing ${PROJECT_NAME} in namespace ${PROJECT_NAMESPACE}"
)
include(GNUInstallDirs)
include(GenerateExportHeader)
include(CMakePackageConfigHelpers)
message(
  STATUS "[${PROJECT_NAME}] installing in prefix: ${CMAKE_INSTALL_PREFIX}")

set(PROJECT_CONFIG_FILE_IN
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in")
set(PROJECT_CONFIG_FILE
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake")
set(CONFIG_TARGETS_FILE "${PROJECT_NAME}-config-targets.cmake")
set(CONFIG_VERSION_FILE
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake")
set(INSTALL_EXPORT_DESTINATION_DIR
    "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(
  DIRECTORY
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/labs_engine>
    $<INSTALL_INTERFACE:include/labs_engine> ;
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
export(
  TARGETS ${PROJECT_NAME}
  NAMESPACE ${PROJECT_NAMESPACE}
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_TARGETS_FILE}")
install(
  EXPORT ${PROJECT_NAME}
  DESTINATION ${INSTALL_EXPORT_DESTINATION_DIR}
  NAMESPACE ${PROJECT_NAMESPACE}
  FILE ${CONFIG_TARGETS_FILE})
configure_package_config_file(
  ${PROJECT_CONFIG_FILE_IN} ${PROJECT_CONFIG_FILE}
  INSTALL_DESTINATION ${INSTALL_EXPORT_DESTINATION_DIR})
write_basic_package_version_file(${CONFIG_VERSION_FILE}
                                 COMPATIBILITY AnyNewerVersion)
install(FILES ${PROJECT_CONFIG_FILE} ${CONFIG_VERSION_FILE}
        DESTINATION ${INSTALL_EXPORT_DESTINATION_DIR})

message(STATUS "[${PROJECT_NAME}] configuring ${PROJECT_NAME} done!")

if(STANDALONE)
  message(STATUS "[${PROJECT_NAME}] building test executable for developers")
  add_subdirectory(bin)
endif()
unset(STANDALONE CACHE)
