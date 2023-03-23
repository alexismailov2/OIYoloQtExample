#!/bin/bash

#export PATH=$PATH:"/c/Qt/Tools/mingw1120_64/bin"
export PATH=$PATH:"/c/Qt/Qt5.12.12_/Tools/mingw730_64/bin"

cmake -Bbuild_win32 \
-DCMAKE_GENERATOR="Ninja" \
-DCMAKE_MAKE_PROGRAM="/c/Qt/Tools/Ninja/ninja.exe" \
-DCMAKE_BUILD_TYPE=Release \
-DQT_QMAKE_EXECUTABLE="/c/Qt/Qt5.12.12_/Tools/mingw730_64/bin/qmake.exe" \
-DCMAKE_PREFIX_PATH="/c/Qt/Qt5.12.12_/5.12.12/mingw73_64" \
-DCMAKE_C_COMPILER="/c/Qt/Qt5.12.12_/Tools/mingw730_64/bin/gcc.exe" \
-DCMAKE_CXX_COMPILER="/c/Qt/Qt5.12.12_/Tools/mingw730_64/bin/g++.exe" \
-DCMAKE_CXX_FLAGS_INIT="-DQT_QML_DEBUG" \
-DCMAKE_INSTALL_PREFIX=$(pwd)/Install
cmake --build build_win32 --target dependencies
cmake --build build_win32 --target NcnnYolov8_test1
