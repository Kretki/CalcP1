cmake_minimum_required(VERSION 3.5)

project(CalcP LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Core Svg REQUIRED)

set(QWT_ROOT /usr/local/qwt-6.3.0)
set(QWT_INCLUDE_DIR ${QWT_ROOT}/include)
set(QWT_LIBRARY_DIR ${QWT_ROOT}/lib)

include_directories(${QWT_INCLUDE_DIR})
link_directories(${QWT_LIBRARY_DIR})
set(QWT_LIBRARIES ${QWT_LIBRARY_DIR}/libqwt.so)

add_executable(CalcP
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  togglewidget.h
  togglewidget.cpp
  inputwidget.h
  inputwidget.cpp
  calculatorwidget.h
  calculatorwidget.cpp
  calculatorwidgetfunctions.cpp
)

target_link_libraries(CalcP PRIVATE Qt5::Core Qt5::Widgets Qt5::Svg)
target_link_libraries(CalcP PRIVATE ${QWT_LIBRARIES})

configure_file(inputRLS.txt ${CMAKE_BINARY_DIR}/inputRLS.txt COPYONLY)
configure_file(inputSig.txt ${CMAKE_BINARY_DIR}/inputSig.txt COPYONLY)
configure_file(inputTarg.txt ${CMAKE_BINARY_DIR}/inputTarg.txt COPYONLY)
configure_file(inputNoise.txt ${CMAKE_BINARY_DIR}/inputNoise.txt COPYONLY)
configure_file(inputReceiver.txt ${CMAKE_BINARY_DIR}/inputReceiver.txt COPYONLY)