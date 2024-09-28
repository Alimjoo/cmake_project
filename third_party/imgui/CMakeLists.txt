cmake_minimum_required(VERSION 3.18)

# Set project name for the library
set(Proj_Name imgui)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Vulkan prototypes definition
add_definitions(-DVK_PROTOTYPES)

# GLFW setup (assuming you include GLFW as well)
set(GLFW_DIR ../glfw) # Adjust path to your GLFW repository
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
option(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)
add_subdirectory(${GLFW_DIR} binary_dir EXCLUDE_FROM_ALL)
include_directories(${GLFW_DIR}/include ${GLFW_DIR}/deps) # Include GLFW headers and deps

# Dear ImGui setup
set(IMGUI_DIR ./)
# include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends ..)

# Find Vulkan package
find_package(Vulkan REQUIRED)

# Set libraries to link
set(LIBRARIES glfw Vulkan::Vulkan)

# Add ImGui source files
file(GLOB IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
)

# Create library
add_library(${Proj_Name} STATIC ${IMGUI_SOURCES})

target_include_directories(${Proj_Name} PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# Link libraries
target_link_libraries(${Proj_Name} ${LIBRARIES})

# Add definition for ImTextureID
target_compile_definitions(${Proj_Name} PUBLIC -DImTextureID=ImU64)
