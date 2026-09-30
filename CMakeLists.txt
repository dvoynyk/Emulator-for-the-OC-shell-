cmake_minimum_required(VERSION 3.16)

project(shell-emulator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        MainWindow.cpp
        SystemInfo.cpp
        Parser.cpp
        Executor.cpp
        ConfigParser.cpp
        ScriptExecutor.cpp

        MainWindow.h
        SystemInfo.h
        Parser.h
        Executor.h
        ConfigParser.h
        ScriptExecutor.h
)

if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    qt_add_executable(shell-emulator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(shell-emulator
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(shell-emulator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(shell-emulator)
endif()