cmake_minimum_required(VERSION 3.5)

project(ur5GripperControler LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

include_directories("/usr/include/modbus/")
include_directories("/usr/include/mysql/")
link_directories("/usr/lib/x86_64-linux-gnu/")


find_package(Qt5 COMPONENTS Widgets REQUIRED)



if(ANDROID)
  add_library(ur5GripperControler SHARED
    main.cpp
    widget.cpp
    widget.h
    widget.ui
    ur5andgripper.cpp
    ur5andgripper.h
  )
else()
  add_executable(ur5GripperControler
    main.cpp
    widget.cpp
    widget.h
    widget.ui
    ur5andgripper.cpp
    ur5andgripper.h
  )
endif()

target_link_libraries(ur5GripperControler PRIVATE Qt5::Widgets modbus mysqlclient)
