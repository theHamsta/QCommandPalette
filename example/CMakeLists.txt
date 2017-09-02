
    
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    )

qt5_wrap_cpp(EXAMPLE_MOC MainWindow.hpp)
qt5_wrap_ui(EXAMPLE_UI MainWindow.ui)

add_executable(qcommandpalette_test
					main.cpp 
					MainWindow.cpp
					MainWindow.hpp
					MainWindow.ui
					${EXAMPLE_MOC}
			    )


target_link_libraries(qcommandpalette_test qcommandpalette)

