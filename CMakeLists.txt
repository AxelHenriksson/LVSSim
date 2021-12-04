cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

# set the project name
project(CGraphics VERSION 0.1)

# configure header to pass the version number to source code
configure_file(src/headers/CGraphicsConfig.h.in CGraphicsConfig.h)

#add libraries
add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
  IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/lib/libglfw3.a"
  INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/inc/GLFW"
)

set(CGraphicsSources  
                      "src/glad.c" 
                      "src/stb.cpp"

                      "src/CGraphics.cpp"
                      "src/EBO.cpp" 
                      "src/VBO.cpp" 
                      "src/VAO.cpp" 
                      "src/Shader.cpp"
                      "src/Texture.cpp"
                      )

# add the executable
add_executable(CGraphics ${CGraphicsSources})

target_link_libraries(CGraphics glfw)

target_include_directories(CGraphics PUBLIC 
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/src/headers"
                            "${PROJECT_SOURCE_DIR}/inc"
                            )

                            
#Testing
include(CTest)
add_executable(TestInstantiator test/TestInstantiator.cpp)
add_test(NAME TestInstantiator
         COMMAND TestInstantiator)