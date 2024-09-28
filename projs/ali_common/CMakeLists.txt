set(Proj_Name ali_common)

file(GLOB ALL_FILES "headers/*.h" "sources/*.cpp")

# Find OpenCV
if(WIN32)
    # set(OpenCV_DIR "C:/Users/PI/Documents/opencv/build/x64/vc16/lib")
    set(OpenCV_DIR "C:/Users/PI/Documents/opencv/build/")
    # set(OpenCV_DIR "C:/Users/PI/Documents/opencv/sources/build/")
endif()
find_package(OpenCV REQUIRED)

add_library(${Proj_Name} ${ALL_FILES})

target_include_directories(${Proj_Name} PUBLIC 
    ./headers 
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(${Proj_Name} PUBLIC 
    ${OpenCV_LIBS}
)


