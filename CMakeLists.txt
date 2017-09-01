cmake_minimum_required(VERSION 2.6)
project(qcommandpalette)

set(QT_MIN_VERSION "5.3.0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

find_package( Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Gui Widgets )
find_package( Qt5LinguistTools )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    )
    
aux_source_directory( source ${SOURCES} )

file(GLOB UI RELATIVE  "${CMAKE_CURRENT_SOURCE_DIR}" ${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui )
file(GLOB UI_INCLUDES RELATIVE  "${CMAKE_CURRENT_SOURCE_DIR}" ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp )
qt5_wrap_cpp(MOC_SRC ${UI_INCLUDES})
# qt5_wrap_ui(MOC_UI ${UI})
file(GLOB TRANSLATION_SOURCES  ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp )
file(GLOB TRANSLATION_INCLUDE  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp )
# if( CMAKE_BUILD_TYPE STREQUAL "Release" AND Qt5LinguistTools_FOUND)
qt5_create_translation( foo.qm ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp  ${TRANSLATION_INCLUDE} ${UI} ${TRANSLATION_SOURCES} translation_de.ts )
qt5_add_translation( TRANSLATIONS translation_de.ts )

add_executable(qcommandpalette
		main.cpp 
		${SOURCES}
		${MOC_SRC}
		${UI}
		${TRANSLATIONS}
    )
target_link_libraries(qcommandpalette ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS qcommandpalette RUNTIME DESTINATION bin)
