cmake_minimum_required(VERSION 3.5)

project(CalcP LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

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
)

target_link_libraries(CalcP PRIVATE Qt5::Core Qt5::Widgets)
target_link_libraries(CalcP PRIVATE ${QWT_LIBRARIES})
