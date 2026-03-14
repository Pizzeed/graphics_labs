add_executable(${PROJECT_NAME}-bench)

target_sources(${PROJECT_NAME}-bench
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/cube.cc
)

target_link_libraries(${PROJECT_NAME}-bench
        PRIVATE
        ${PROJECT_NAME}
)

add_compile_definitions("SOURCE_ROOT=${CMAKE_SOURCE_DIR}")

