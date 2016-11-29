cmake_minimum_required (VERSION 3.7.0)

project (Logic)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
 
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
 
message ("cxx Flags:" ${CMAKE_CXX_FLAGS})
 
# Sub-directories where more CMakeLists.txt exist
add_subdirectory(app)
add_subdirectory (algo)