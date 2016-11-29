file (GLOB ALGO_SOURCES
      "*.h")
 
# Collect sources into the variable SIMPLE_FUNCTION_SOURCES
set (SUDOKU_FUNCTION_SOURCES
      "Sudoku/Sudoku.h"
      "Sudoku/Sudoku.cpp")
 
set  (SUDOKUMATRIX_FUNCTION_SOURCES
      "SudokuMatrix/SudokuMatrix.h"
      "SudokuMatrix/SudokuMatrix.cpp")
 
source_group("" FILES ${ALGO_SOURCES})
source_group("sudoku" FILES ${SUDOKU_FUNCTION_SOURCES})
source_group("sudokumatrix" FILES ${SUDOKUMATRIX_FUNCTION_SOURCES})
 
include_directories (.)
 
add_library(algo SHARED ${ALGO_SOURCES} 
                        ${SUDOKU_FUNCTION_SOURCES} 
                        ${SUDOKUMATRIX_FUNCTION_SOURCES})
 
set_property(TARGET algo PROPERTY FOLDER "libraries")
 
install (TARGETS algo
         RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)