cmake_minimum_required(VERSION 3.16)

project(PEOJEKTPK VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dodaj Qt Charts do listy wymaganych komponentów
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        App.cpp
        App.h
        ARX.cpp
        ARX.h
        BuforDanych.cpp
        BuforDanych.h
        PID.cpp
        PID.h
        Sprzezenie.cpp
        Sprzezenie.h
        Sygnal.cpp
        Sygnal.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PEOJEKTPK
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        zasoby.qrc

    )
else()
    if(ANDROID)
        add_library(PEOJEKTPK SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(PEOJEKTPK
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Linkowanie modułu Qt Charts i Widgets
target_link_libraries(PEOJEKTPK PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.PEOJEKTPK)
endif()
set_target_properties(PEOJEKTPK PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS PEOJEKTPK
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PEOJEKTPK)
endif()
