project(lib)

find_package(Qt5Widgets)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

add_library(lib STATIC
	gui.h
	gui.cpp
)

target_link_libraries(lib
     Qt5::Widgets
)