project(lib)

find_package(Qt5Widgets)
find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

add_library(lib STATIC
	gui.h
	gui.cpp
	Sudoku.h
	Sudoku.cpp
	Sudoku1.h
	Sudoku1.cpp
	SudokuMatrix.h
	SudokuMatrix.cpp
	TrainAndTest.h
	TrainAndTest.cpp
)

target_link_libraries(lib
	Qt5::Widgets
	${OpenCV_LIBS}
)