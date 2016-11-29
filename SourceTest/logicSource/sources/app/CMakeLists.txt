include_directories ("${PROJECT_SOURCE_DIR}/algo")
 
add_executable (app Main.cpp)
 
target_link_libraries (app algo)
 
set_property(TARGET app PROPERTY FOLDER "executables")
 
install (TARGETS app
         RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)