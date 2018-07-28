cmake_minimum_required(VERSION 2.6)
project(qcommandpalette)


set(QT_MIN_VERSION "5.3.0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package( Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Gui Widgets )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/fuzzy-native/src/
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    )
    

aux_source_directory( source SOURCES )
set( FUZZY_SOURCES   ${CMAKE_CURRENT_SOURCE_DIR}/fuzzy-native/src/MatcherBase.cpp ${CMAKE_CURRENT_SOURCE_DIR}/fuzzy-native/src/score_match.cpp   )

file(GLOB UI RELATIVE  "${CMAKE_CURRENT_SOURCE_DIR}" ${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui )
file(GLOB UI_INCLUDES RELATIVE  "${CMAKE_CURRENT_SOURCE_DIR}" ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp )
qt5_wrap_cpp(MOC_SRC ${UI_INCLUDES})
qt5_wrap_ui(MOC_UI ${UI})

add_library( qcommandpalette
        ${SOURCES}
        ${FUZZY_SOURCES} 
		${MOC_SRC}
		${UI}
		${UI_INCLUDES}
		)
target_link_libraries(qcommandpalette ${Qt5Widgets_LIBRARIES})

add_subdirectory( example )