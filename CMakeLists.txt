cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 17)
project(project_test VERSION 1.0)

# third-party
add_subdirectory(third_party/matplotplusplus)
add_subdirectory(third_party/tinyply)

add_subdirectory(projs/ali_common)
add_subdirectory(projs/demura)
add_subdirectory(projs/HeadSet_Measure_3D)


file(GLOB SOURCES_FILES "src/*.h" "src/*.cpp" main.cpp)
include_directories(src)

add_executable(${PROJECT_NAME} ${SOURCES_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE 
    # third-party
    matplot
    tinyply
    # mine
    ali_common 
    demura
    hsm_3d 
    
)


