project(Prototype)

include_directories ("${lib_SOURCE_DIR}")
 
add_executable(app
	MainApp.cpp
)
 
target_link_libraries(app lib)