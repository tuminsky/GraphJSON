cmake_minimum_required(VERSION 3.5)

project(GraphJSON LANGUAGES CXX)

if (WIN32)
  set(EXEC_FLAG WIN32)
endif()

add_executable(${PROJECT_NAME} ${EXEC_FLAG})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  message("Debug mode")
else()
  message("Release mode")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
  AUTOMOC ON
  AUTOUIC ON
  AUTORCC ON

  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON

  CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0"
  CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2"

  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/debug/"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/release/"
)

set(SRC
  main.cpp
  keysmanager/keysmanager.cpp
  graph/graph.cpp
  controller/controller.cpp
  resources/qml.qrc
)

find_package(Qt6 COMPONENTS Widgets Qml Quick REQUIRED)
find_package(Boost REQUIRED)

find_program(GRAPHVIZ_FOUND "dot")

if (!GRAPHVIZ_FOUND)
  message(FATAL_ERROR "Graphviz not found. CMake will exit.")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIR})
target_sources(${PROJECT_NAME} PRIVATE ${SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Qml Qt6::Quick ${Boost_LIBRARIES})
