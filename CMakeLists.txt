find_package(OpenCV    3.0.0    REQUIRED)
project(OpenCVProject)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
)
add_executable(OpenCVProject
    Source.cpp
)

target_link_libraries(OpenCVProject
    ${OpenCV_LIBS}
)