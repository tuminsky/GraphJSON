cmake_minimum_required(VERSION 3.5)

project(dev_os_homework_2 LANGUAGES CXX)

add_executable(dev_os_homework)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  message("Debug mode")
else()
  message("Release mode")
endif()

set_target_properties(dev_os_homework PROPERTIES
  AUTOMOC ON
  AUTOUIC ON

  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON

  CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0"
  CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2"

  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/debug/"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/release/"
)

set(GUI_SRC
  gui/mainwindow/mainwindow.cpp
  gui/mainwindow/mainwindow.ui

  gui/customgraphicsview/customgraphicsview.cpp

  gui/graph/node.cpp

  gui/graph/edge.cpp
)

set(UTIL_SRC
  util/keysmanager/keysmanager.cpp
)

set(SRC main.cpp
  ${GUI_SRC}
  ${UTIL_SRC}
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

target_include_directories(dev_os_homework PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(dev_os_homework PRIVATE ${SRC})
target_link_libraries(dev_os_homework PRIVATE Qt5::Core Qt5::Widgets)
