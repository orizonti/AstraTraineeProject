cmake_minimum_required(VERSION 3.14)
project(TRAINEE_ASTRA_PROJECT)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ./ui_files)
set(UNICODE 1)
set(QT_NO_DEBUG 1)
set(NDEBUG 1)
set(QT_CORE_LIB 1)
set(QT_GUI_LIB 1)
set(QT_NETWORK_LIB 1)
set(QT_SERIALPORT_LIB 1)
set(QT_WIDGETS_LIB 1)
set(QT_PRINTSUPPORT_LIB 1)

#add_compile_options(-DQT_NO_WARNING_OUTPUT)
message("MAIN PROJECT CONFIG")

set(USER "broms")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(LIBRARY_DIR "/home/${USER}/LIBRARY")
set(OPENCV_LIB_DIR  "${LIBRARY_DIR}/IMAGE_PROCESSING/OPENCV/opencv451")

cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH PROJECT_DIR)
message("PROJECT SOURCE : "${PROJECT_SOURCE_DIR})
message("PROJECT DIR    : "${PROJECT_DIR})
message("BUILD_DIR      : "${PROJECT_BINARY_DIR})
message("ROTATE LIB     : ${PROJECT_BINARY_DIR}/rotate_optimization/libRotateOptimization.so")
message("LIBRARIES      : "${LIBRARY_DIR})

list(APPEND CMAKE_PREFIX_PATH "${LIBRARY_DIR}/NN_LIBRARY/LIBTORCH/libtorch/")
list(APPEND CMAKE_PREFIX_PATH "${LIBRARY_DIR}/QT5.15.2/5.15.2/gcc_64/")
list(APPEND CMAKE_PREFIX_PATH "${OPENCV_LIB_DIR}")

#====================================================
if(NOT EXISTS "/home/${USER}/LIBRARY")
message("LIBRARY: /home/${USER}/LIBRARY NOT EXIST ERROR !!!!")
endif()

find_package(Torch REQUIRED)
find_package(Qt5 COMPONENTS Widgets Network Core SerialPort PrintSupport REQUIRED)
find_package(OpenCV REQUIRED )
message("OPENCV LIBS "${OpenCV_LIBS})

add_subdirectory(rotate_optimization)
#====================================================
include_directories("${PROJECT_SOURCE_DIR}/rotate_optimization")

include_directories("/opt/nf_npkspp/ibpa.08072-01_mppd_driver/include/headers/")
include_directories("/usr/local/include/opencv4")
include_directories("./gui_sources")
include_directories("./LASERS")
include_directories("./REMOTE_CONTROL")
include_directories(${PROJECT_SOURCE_DIR})

include_directories("${LIBRARY_DIR}/COMMON_LIBRARRY/boost_1_68_0/boost_1_68_0")
include_directories("${LIBRARY_DIR}/MATH_LIBRARY")

include_directories("${LIBRARY_DIR}/NN_LIBRARY/LIBTORCH/libtorch/include")
include_directories("${LIBRARY_DIR}/NN_LIBRARY/LIBTORCH/libtorch/include/torch/csrc/api/include")
include_directories("${LIBRARY_DIR}/NN_LIBRARY/ONNX/onnxruntime/include/")
link_directories("${LIBRARY_DIR}/NN_LIBRARY/ONNX/onnxruntime/lib/")
#====================================================

add_executable (TraineeProjectExecutable
        "./ui_files/aimingblockwindow.ui"
        "./ui_files/cameracontrolwindow.ui"
        "./ui_files/camerawindow.ui"
        "./ui_files/engineblockwindow.ui"
        "./ui_files/enginecontrolwindow.ui"
        "./ui_files/RemoteAimingWindowControl.ui"
        "./ui_files/RemoteCommandDisplay.ui"
        "./ui_files/graphicswindow.ui"
        "./ui_files/imageprocessingdisplaywindow.ui"
        "./ui_files/imageprocessingwindow.ui"
        "./ui_files/kalmanwindow.ui"
        "./ui_files/laserblockwindow.ui"
        "./ui_files/mainblockwindow.ui"
        "./ui_files/mainwindowclass.ui"
        "./ui_files/pid_control_window.ui"
        "./ui_files/PilotLaserWindow.ui"
        "./ui_files/windowsinussource.ui"
        "./ui_files/ChillerWindowDisplay.ui"

        "./gui_sources/aimingblockwindow.cpp"
        "./gui_sources/engineblockwindow.cpp"
        "./gui_sources/cameracontrolwindow.cpp"
        "./gui_sources/camerawindow.cpp"
        "./gui_sources/graphicswindow.cpp"
        "./gui_sources/imageprocessingdisplaywindow.cpp"
        "./gui_sources/imageprocessingwindow.cpp"
        "./gui_sources/mainblockwindow.cpp"
        "./gui_sources/mainwindowclass.cpp"
        "./gui_sources/kalmanwindow.cpp"
        "./gui_sources/laserblockwindow.cpp"
        "./gui_sources/enginecontrolwindow.cpp"
        "./gui_sources/graphicwidgetnode.cpp"
        "./gui_sources/pid_control_window.cpp"
        "./gui_sources/PilotLaserWindow.cpp"
        "./gui_sources/windowsinussource.cpp"
        "./gui_sources/AdjustableWidget.cpp"
        "./gui_sources/RemoteAimingWindowControl.cpp"
        "./gui_sources/RemoteWindowControl.cpp"
        "./gui_sources/labelimage.cpp"
        "./gui_sources/link_line.cpp"
        "./gui_sources/node.cpp"
        "./gui_sources/ChillerWindowDisplay.cpp"

        "main.cpp"
        "AimingClass.cpp"
        "CameraInterfaceClass.cpp"
        "DigitalClock.cpp"
        "EngineControlClass.cpp"
        "EngineInterfaceClass.cpp"
        "ImageProcessingClass.cpp"
        "KLPInterfaceClass.cpp"
        "chillerinterface.cpp"

        "./LASERS/LaserControlClass.cpp"
        "./LASERS/LaserCommonInterface.cpp"
        "./LASERS/LaserPilotInterface.cpp"
        "./LASERS/LaserPointerInterface.cpp"
        "./LASERS/LaserPowerInterface.cpp"

        "./REMOTE_CONTROL/RemoteControlInterface.cpp"
        "./REMOTE_CONTROL/RemoteControlProtocol.cpp"
        "./REMOTE_CONTROL/UDPEngineInterface.cpp"
        
        "main.cpp"
        "maincontrollerclass.cpp"

        "PassTwoCoordClass.cpp"
        "PIDClass.cpp"
        "qcustomplot.cpp"
        "SinusGeneratorClass.cpp"
        "TransformCoordClass.cpp"
        "mppd_wrap.cpp"
        "qcustomplot.h"
        "KalmanFilterClass.cpp"
        "KalmanFilterClass.h"
        )

#=========================================================
target_link_libraries(TraineeProjectExecutable ${OpenCV_LIBS})
target_link_libraries(TraineeProjectExecutable Qt5::Widgets)
target_link_libraries(TraineeProjectExecutable Qt5::Network)
target_link_libraries(TraineeProjectExecutable Qt5::Core)
target_link_libraries(TraineeProjectExecutable Qt5::SerialPort)
target_link_libraries(TraineeProjectExecutable Qt5::PrintSupport)
target_link_libraries(TraineeProjectExecutable onnxruntime.so)
target_link_libraries(TraineeProjectExecutable "${PROJECT_BINARY_DIR}/rotate_optimization/libRotateOptimization.so")

#link_directories("${LIBRARY_DIR}/NN_LIBRARY/libtorch/lib")
target_link_libraries(TraineeProjectExecutable "${LIBRARY_DIR}/NN_LIBRARY/LIBTORCH/libtorch/lib/libtorch_cpu.so")
target_link_libraries(TraineeProjectExecutable "${LIBRARY_DIR}/NN_LIBRARY/LIBTORCH/libtorch/lib/libtorch.so")
target_link_libraries(TraineeProjectExecutable "${LIBRARY_DIR}/NN_LIBRARY/LIBTORCH/libtorch/lib/libc10.so")
include_directories("./DataTypes")
#=========================================================

#include_directories("/home/broms/DEVELOPMENT/PROJECTS/ASTRA_PROJECT/AstraTraineeProject/build/TraineeProjectSource/TraineeProjectExecutable_autogen/include/")


# TODO: Добавьте тесты и целевые объекты, если это необходимо.
