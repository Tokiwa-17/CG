CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(PA0 CXX)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)
ENDIF()

ADD_SUBDIRECTORY(deps/vecmath)

SET(PA0_SOURCES
        src/image.cpp
        src/main.cpp
        src/canvas_parser.cpp)

SET(PA0_INCLUDES
        include/image.hpp
        include/canvas_parser.hpp
        include/element.hpp)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(${PROJECT_NAME} ${PA0_SOURCES} ${PA0_INCLUDES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} vecmath)
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE include)
