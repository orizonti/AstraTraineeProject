cmake_minimum_required(VERSION 3.14)
project(TestClionQt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ./ui_files)
#"/home/broms/DEVELOPMENT/ASTRA_PROJECT/TestCmakeTrainee/TestCmakeProject/ErrorPortControl.ui"
set(UNICODE 1)
set(WIN32 1)
set(WIN64 1)
set(QT_NO_DEBUG 1)
set(NDEBUG 1)
set(QT_CORE_LIB 1)
set(QT_GUI_LIB 1)
set(QT_NETWORK_LIB 1)
set(QT_SERIALPORT_LIB 1)
set(QT_WIDGETS_LIB 1)
set(QT_PRINTSUPPORT_LIB 1)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(EXISTS "/home/broms/PROGRAM_LIBRARY/linux/QT5.15/5.15.2/gcc_64/")
    set(CMAKE_PREFIX_PATH "/home/broms/PROGRAM_LIBRARY/linux/QT5.15/5.15.2/gcc_64/")
    set(Qt5Core_DIR "/home/broms/PROGRAM_LIBRARY/linux/QT5.15/5.15.2/gcc_64/Qt5Core")
    set(Qt5Gui_DIR "/home/broms/PROGRAM_LIBRARY/linux/QT5.15/5.15.2/gcc_64/Qt5Gui")
    set(Qt5Network "/home/broms/PROGRAM_LIBRARY/linux/QT5.15/5.15.2/gcc_64/Qt5Network")
    set(Qt5PrintSupport "/home/broms/PROGRAM_LIBRARY/linux/QT5.15/5.15.2/gcc_64/Qt5PrintSupport")
    set(Qt5SerialPort "/home/broms/PROGRAM_LIBRARY/linux/QT5.15/5.15.2/gcc_64/Qt5SerialPort")
    set(Qt5Widgets "/home/broms/PROGRAM_LIBRARY/linux/QT5.15/5.15.2/gcc_64/Qt5Widgets")
    set(Qt5 "/home/broms/PROGRAM_LIBRARY/linux/QT5.15/5.15.2/gcc_64/Qt5")
    endif()

if(EXISTS "/home/broms/Qt/5.15.2/gcc_64")
    set(CMAKE_PREFIX_PATH "/home/broms/Qt/5.15.2/gcc_64")
    set(Qt5Core_DIR "/home/broms/Qt/5.15.2/gcc_64/lib/cmake/Qt5Core")
    set(Qt5Gui_DIR "/home/broms/Qt/5.15.2/gcc_64/lib/cmake/Qt5Gui")
    set(Qt5Network "/home/broms/Qt/5.15.2/gcc_64/lib/cmake/Qt5Network")
    set(Qt5PrintSupport "/home/broms/Qt/5.15.2/gcc_64/lib/cmake/Qt5PrintSupport")
    set(Qt5SerialPort "/home/broms/Qt/5.15.2/gcc_64/lib/cmake/Qt5SerialPort")
    set(Qt5Widgets "/home/broms/Qt/5.15.2/gcc_64/lib/cmake/Qt5Widgets")
    set(Qt5 "/home/broms/Qt/5.15.2/gcc_64/lib/cmake/Qt5")
    endif()


find_package(Qt5 COMPONENTS Widgets Network Core SerialPort PrintSupport REQUIRED)

set(CMAKE_PREFIX_PATH "/home/broms/COMMON_DIR/PROGRAM_LIBRARY/NN_LIBRARY/libtorch/")
find_package(Torch REQUIRED)

find_package(OpenCV REQUIRED )
message("OPENCV LIBS "${OpenCV_LIBS})
# Добавьте источник в исполняемый файл этого проекта.

include_directories("/opt/nf_npkspp/ibpa.08072-01_mppd_driver/include/headers/")
include_directories("/usr/local/include/opencv4")

link_directories(/home/broms/COMMON_DIR/PROGRAM_LIBRARY/NN_LIBRARY/libtorch/lib)
include_directories("/home/broms/COMMON_DIR/PROGRAM_LIBRARY/NN_LIBRARY/libtorch/include")
include_directories("/home/broms/COMMON_DIR/PROGRAM_LIBRARY/NN_LIBRARY/libtorch/include/torch/csrc/api/include")
include_directories("/home/broms/COMMON_DIR/PROGRAM_LIBRARY/MATH_LIBRARY")
include_directories("/home/broms/COMMON_DIR/PROGRAM_LIBRARY/COMMON_LIBRARRY/boost_1_68_0/boost_1_68_0")

#================================


add_executable (TestCmakeProject
        "./ui_files/aimingblockwindow.ui"
        "./ui_files/cameracontrolwindow.ui"
        "./ui_files/camerawindow.ui"
        "./ui_files/engineblockwindow.ui"
        "./ui_files/enginecontrolwindow.ui"
        "./ui_files/ErrorPortControl.ui"
        "./ui_files/graphicswindow.ui"
        "./ui_files/imageprocessingdisplaywindow.ui"
        "./ui_files/imageprocessingwindow.ui"
        "./ui_files/kalmanwindow.ui"
        "./ui_files/laserblockwindow.ui"
        "./ui_files/mainblockwindow.ui"
        "./ui_files/mainwindowqclass.ui"
        "./ui_files/pidwindow2.ui"
        "./ui_files/PilotLaserWindow.ui"
        "./ui_files/windowsinussource.ui"

        "ui_PIDWindow.h"
        "main.cpp"
        "aimingblockwindow.cpp"
        "AimingClass.cpp"
        "AimingControlBest.cpp"
        "AirSystemClass.cpp"
        "CalmanFilterClass.cpp"
        "cameracontrolwindow.cpp"
        "CameraInterfaceClass.cpp"
        "camerawindow.cpp"
        "ChillSystemClass.cpp"
        "CommonLaserInterfaceClass.cpp"
        "DigitalClock.cpp"
        "edge.cpp"
        "engineblockwindow.cpp"
        "EngineControlClass.cpp"
        "enginecontrolwindow.cpp"
        "EngineInterfaceClass.cpp"
        "ErrorPortControl.cpp"
        "ErrorRecieverClass.cpp"
        "graphicswindow.cpp"
        "graphicwidgetnode.cpp"
        "ImageProcessingClass.cpp"
        "imageprocessingdisplaywindow.cpp"
        "imageprocessingwindow.cpp"
        "kalmanwindow.cpp"
        "KLPInterfaceClass.cpp"
        "labelimage.cpp"
        "laserblockwindow.cpp"
        "LaserControlClass.cpp"
        "LaserPilotInterfaceClass.cpp"
        "LaserPointerInterfaceClass.cpp"
        "LaserPowerInterfaceClass.cpp"
        "main.cpp"
        "mainblockwindow.cpp"
        "maincontrollerqclass.cpp"
        "mainwindowqclass.cpp"
        "node.cpp"
        "PassTwoCoordClass.cpp"
        "PIDClass.cpp"
        "pidwindow2.cpp"
        "PilotLaserWindow.cpp"
        "qcustomplot.cpp"
        "RemoteControlClass.cpp"
        "RotateOperationContainer.cpp"
        "SinusGeneratorClass.cpp"
        "stdafx.cpp"
        "tcpclientengine.cpp"
        "TransformCoordClass.cpp"
        "windowsinussource.cpp"
        "mppd_wrap.cpp"
        "qcustomplot.h"
        )
#target_link_libraries(TestClionQt DriverMoiKlp.lib)
target_link_libraries(TestCmakeProject ${OpenCV_LIBS})
target_link_libraries(TestCmakeProject Qt5::Widgets)
target_link_libraries(TestCmakeProject Qt5::Network)
target_link_libraries(TestCmakeProject Qt5::Core)
target_link_libraries(TestCmakeProject Qt5::SerialPort)
target_link_libraries(TestCmakeProject Qt5::PrintSupport)
target_link_libraries(TestCmakeProject libtorch_cpu.so)
target_link_libraries(TestCmakeProject libtorch.so)
target_link_libraries(TestCmakeProject libc10.so)

#set(Qt5Core_DIR "/home/broms/Qt/5.15.2/gcc_64/lib/cmake/Qt5Core")
#set(Qt5Gui_DIR "/home/broms/Qt/5.15.2/gcc_64/lib/cmake/Qt5Gui")
#set(Qt5Network "/home/broms/Qt/5.15.2/gcc_64/lib/cmake/Qt5Network")
#set(Qt5PrintSupport "/home/broms/Qt/5.15.2/gcc_64/lib/cmake/Qt5PrintSupport")
#set(Qt5SerialPort "/home/broms/Qt/5.15.2/gcc_64/lib/cmake/Qt5SerialPort")
#set(Qt5Widgets "/home/broms/Qt/5.15.2/gcc_64/lib/cmake/Qt5Widgets")
#set(Qt5 "/home/broms/Qt/5.15.2/gcc_64/lib/cmake/Qt5")
set(QtIncludeCore "/home/broms/Qt/5.15.2/gcc_64/include/QtCore")
set(QtIncludeGui "/home/broms/Qt/5.15.2/gcc_64/include/QtGui")
set(QtIncludeWidgets "/home/broms/Qt/5.15.2/gcc_64/include/QtWidgets")
set(QtIncludeNetwork "/home/broms/Qt/5.15.2/gcc_64/include/QtNetwork")
set(QtIncludeSerialPort "/home/broms/Qt/5.15.2/gcc_64/include/QtSerialPort")
set(QtIncludeConcurrent "/home/broms/Qt/5.15.2/gcc_64/include/QtConcurrent")
set(IncludeBoost "/home/broms/COMMON_DIR/PROGRAM_LIBRARY/COMMON_LIBRARRY/boost_1_68_0/boost_1_68_0")
set(IncludeMath "/home/broms/COMMON_DIR/PROGRAM_LIBRARY/MATH_LIBRARY")
set(IncludeTorch "/home/broms/COMMON_DIR/PROGRAM_LIBRARY/NN_LIBRARY/libtorch/include/torch/csrc/api/include")



target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeSerialPort}/QSerialPort)

target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeCore}/qobject.h)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeCore}/qdebug.h)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeCore}/qtimer.h)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeCore}/QTime)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeCore}/qthread.h)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeCore}/qbytearray.h)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeCore}/qdatastream.h)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeCore}/QTimer)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeCore}/QString)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeCore}/QList)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeCore}/QPair)

target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeNetwork}/QTcpSocket)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeNetwork}/QHostAddress)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeNetwork}/QTcpServer)

target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeGui}/qimage.h)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeGui}/qpixmap.h)

target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeWidgets}/QWidget)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeWidgets}/QLCDNumber)

target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeWidgets}/QGraphicsProxyWidget)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeWidgets}/QGraphicsScene)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeWidgets}/QWidget)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeWidgets}/QSpinBox)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeWidgets}/QDoubleSpinBox)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeWidgets}/QLabel)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeWidgets}/QGraphicsItem)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeWidgets}/QGraphicsScene)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeWidgets}/QtWidgets)

target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeGui}/QPainterPath)

target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeCore}/QSettings)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeCore}/QFile)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeCore}/QMutex)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeCore}/QWaitCondition)
target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeCore}/QQueue)

target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeConcurrent}/QtConcurrent)


target_precompile_headers(TestCmakeProject PRIVATE ${QtIncludeCore}/QtMath)
target_precompile_headers(TestCmakeProject PRIVATE ${IncludeBoost}/boost/crc.hpp)
target_precompile_headers(TestCmakeProject PRIVATE qcustomplot.h)

set(IncludeMath "/home/broms/COMMON_DIR/PROGRAM_LIBRARY/MATH_LIBRARY")

target_precompile_headers(TestCmakeProject PRIVATE ${IncludeMath}/Eigen/Eigen)
target_precompile_headers(TestCmakeProject PRIVATE ${IncludeMath}/Eigen/Dense)
target_precompile_headers(TestCmakeProject PRIVATE ${IncludeMath}/Eigen/src/Core/Matrix.h)
target_precompile_headers(TestCmakeProject PRIVATE ${IncludeMath}/Eigen/src/Core/Matrix.h)

#target_precompile_headers(TestCmakeProject PRIVATE ${IncludeTorch}/torch/torch.h)

#target_precompile_headers(TestCmakeProject PRIVATE iostream.h)
#target_precompile_headers(TestCmakeProject PRIVATE string.h)
#target_precompile_headers(TestCmakeProject PRIVATE vector.h)
#target_precompile_headers(TestCmakeProject PRIVATE math.h)
#target_precompile_headers(TestCmakeProject PRIVATE chrono.h)




# TODO: Добавьте тесты и целевые объекты, если это необходимо.