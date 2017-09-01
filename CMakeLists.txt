cmake_minimum_required(VERSION 2.6)
project(qcommandpalette)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(QCommandPalette_SRCS QCommandPalette.cpp main.cpp)

qt4_automoc(${QCommandPalette_SRCS})
add_executable(qcommandpalette ${QCommandPalette_SRCS})
target_link_libraries(qcommandpalette ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS qcommandpalette RUNTIME DESTINATION bin)
