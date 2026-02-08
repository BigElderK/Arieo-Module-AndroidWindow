cmake_minimum_required (VERSION 3.31)

include($ENV{ARIEO_BUILDENV_PACKAGE_INSTALL_FOLDER}/cmake/build_environment.cmake)
project(ArieoEngine)

if(CMAKE_SYSTEM_NAME STREQUAL "Android")
arieo_engine_project(
    arieo_android_win_module
    ALIAS arieo::modules::window::android
    PROJECT_TYPE module
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/private/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/private/src/*/*.cpp
    PACKAGES
        game-activity
    INTERFACES
        Arieo-Interface-Window::arieo_window_interface
    PRIVATE_LIBS
        arieo::base
        arieo::core
    LIBS
        game-activity::game-activity_static
        android
        log
)
endif()