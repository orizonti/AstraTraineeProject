cmake_minimum_required(VERSION 3.14)

project(RotateOptimization LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message("ROTATE OPTIMIZATION LIBRARY ADD")
message("PROJECT SOURCE: "${PROJECT_SOURCE_DIR})

#set(LIBRARY_DIR "/home/broms/PROGRAM_LIBRARY")
set(LIBRARY_DIR "/home/broms/PROGRAM_LIBRARY")
#set(LIBRARY_DIR "/mnt/d/PROGRAM_LIBRARY/linux")


if(EXISTS "${LIBRARY_DIR}/QT5.15.2/5.15.2/gcc_64/")
    set(CMAKE_PREFIX_PATH "${LIBRARY_DIR}/QT5.15.2/5.15.2/gcc_64/")
endif()
find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_PREFIX_PATH "${LIBRARY_DIR}/NN_LIBRARY/libtorch/")
find_package(Torch REQUIRED)

add_library(RotateOptimization SHARED
  RotateOptimization_global.h
  RotateOperationContainer.cpp
  RotateOperationContainer.h
)

message("TORCH LINK:  ${LIBRARY_DIR}/NN_LIBRARY/libtorch/lib")
link_directories("${LIBRARY_DIR}/NN_LIBRARY/libtorch/lib")
target_link_libraries(RotateOptimization "/home/broms/PROGRAM_LIBRARY/NN_LIBRARY/libtorch/lib/libtorch_cpu.so")
target_link_libraries(RotateOptimization "/home/broms/PROGRAM_LIBRARY/NN_LIBRARY/libtorch/lib/libtorch.so")
target_link_libraries(RotateOptimization "/home/broms/PROGRAM_LIBRARY/NN_LIBRARY/libtorch/lib/libc10.so")
target_link_libraries(RotateOptimization Qt5::Core)

target_compile_definitions(RotateOptimization PRIVATE ROTATEOPTIMIZATION_LIBRARY)

include_directories("${LIBRARY_DIR}/NN_LIBRARY/libtorch/include")
include_directories("${LIBRARY_DIR}/NN_LIBRARY/libtorch/include/torch/csrc/api/include")
include_directories("/home/broms/DEVELOPMENT/PROJECTS/AstraTraineeProject/TraineeProjectSource")
#include_directories("../${PROJECT_SOURCE_DIR}")