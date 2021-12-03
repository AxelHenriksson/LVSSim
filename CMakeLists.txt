cmake_minimum_required(VERSION 3.10)

# set the project name
project(CGraphics VERSION 0.1)

#add libraries
add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
  IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/lib/libglfw3.a"
  INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/inc/GLFW"
)

# add the executable
add_executable(CGraphics CGraphics.cpp glad.c)



set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# configure header to pass the version number to source code
configure_file(CGraphicsConfig.h.in CGraphicsConfig.h)

target_link_libraries(CGraphics glfw)

target_include_directories(CGraphics PUBLIC 
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}"
                            "${PROJECT_SOURCE_DIR}/inc"
                            )

