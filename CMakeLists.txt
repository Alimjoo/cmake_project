cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 17)
project(project_test VERSION 1.0)

add_subdirectory(projs/ali_common)
add_subdirectory(projs/demura)


file(GLOB SOURCES_FILES "src/*.h" "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE ali_common demura)
