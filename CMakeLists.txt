cmake_minimum_required(VERSION 3.23.0)
project(cad VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

#######################################
# Optional variables
#######################################
set(CAD_TOP_LEVEL_PROJECT ${PROJECT_IS_TOP_LEVEL})
option(CAD_TESTS "Generate the tests target" ${CAD_TOP_LEVEL_PROJECT})
option(CAD_STATIC "Build cad as a static library" YES)

#######################################
# Handle QT auxiliar files
#######################################
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#######################################
# Add external libraries
#######################################
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
add_subdirectory(extern)

#######################################
# Define main target
#######################################
add_executable(cad "")
add_subdirectory(src)

#######################################
# Link main app with all dependencies
#######################################
find_package(Qt5 REQUIRED COMPONENTS OpenGL Widgets)
find_package(OpenGL REQUIRED)
target_link_libraries(cad PUBLIC Qt5::Widgets
                                 Qt5::OpenGL
                                 OpenGL::GL
                                 predicates
                                 compgeom
                                 triangle)