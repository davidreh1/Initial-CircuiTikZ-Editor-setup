cmake_minimum_required(VERSION 3.16)
project(CircuiTikZEditor VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

qt6_standard_project_setup()

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/circuit/circuitelement.cpp
    src/circuit/circuitcanvas.cpp
    src/circuit/tikzgenerator.cpp
)

set(HEADERS
    src/mainwindow.h
    src/circuit/circuitelement.h
    src/circuit/circuitcanvas.h
    src/circuit/tikzgenerator.h
)

qt6_add_executable(circuitikz-editor ${SOURCES} ${HEADERS})

target_link_libraries(circuitikz-editor Qt6::Core Qt6::Widgets Qt6::Gui)

# Set output directory
set_target_properties(circuitikz-editor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
