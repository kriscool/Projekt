project(app)

include_directories ("${algo_SOURCE_DIR}")
 
add_executable(app
	Main.cpp
)
 
target_link_libraries(app algo)