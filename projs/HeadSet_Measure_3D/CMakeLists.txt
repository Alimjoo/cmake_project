set(Proj_Name hsm_3d)

file(GLOB ALL_FILES "headers/*.h" "sources/*.cpp")

add_library(${Proj_Name} ${ALL_FILES})

target_include_directories(${Proj_Name} PUBLIC ./headers)

target_link_libraries(${Proj_Name} PUBLIC 
ali_common
)








