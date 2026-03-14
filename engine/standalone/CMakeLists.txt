find_package(ImGui REQUIRED)

add_executable(${PROJECT_NAME}-bench)

target_sources(${PROJECT_NAME}-bench
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/cube.cc
          
        ${CMAKE_CURRENT_SOURCE_DIR}/bindings/imgui_impl_glfw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/bindings/imgui_impl_opengl3.cpp
)

target_link_libraries(${PROJECT_NAME}-bench
        PRIVATE
        ${PROJECT_NAME}
        imgui::imgui
)

add_compile_definitions(CMAKE_BINARY_DIR="${CMAKE_BINARY_DIR}")

