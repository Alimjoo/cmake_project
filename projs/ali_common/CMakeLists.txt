set(Proj_Name ali_common)

file(GLOB ALL_FILES "headers/*.h" "sources/*.cpp")

# Find OpenCV
find_package(OpenCV REQUIRED)

add_library(${Proj_Name} ${ALL_FILES})

target_include_directories(${Proj_Name} PUBLIC 
    ./headers 
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(${Proj_Name} PUBLIC 
${OpenCV_LIBS}
)


