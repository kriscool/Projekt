project(app)

include_directories ("${lib_SOURCE_DIR}")
 
add_executable(app
	main.cpp
)
 
target_link_libraries(app lib)