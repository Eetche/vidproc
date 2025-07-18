cmake_minimum_required(VERSION 3.10)

project(tosymb)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenCV_STATIC ON)
set(OpenCV_CUDA OFF)
set(OpenCV_DIR "C:/opencv/build") # set your path to opencv/build

set(OpenCV_STATIC ON)
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    Version: ${OpenCV_VERSION}")
message(STATUS "    Libraries: ${OpenCV_LIBS}")
message(STATUS "    Include path: ${OpenCV_INCLUDE_DIRS}")

add_executable(${PROJECT_NAME}
    main.cpp
    vidproc/videoprocess.cpp
    vidproc/videoprocess.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})

