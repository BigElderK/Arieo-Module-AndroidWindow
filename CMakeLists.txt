cmake_minimum_required (VERSION 3.31)

include($ENV{ARIEO_BUILDENV_PACKAGE_INSTALL_FOLDER}/cmake/build_environment.cmake)
project(ArieoEngine)

if(CMAKE_SYSTEM_NAME STREQUAL "Android")
    arieo_engine_project(
        arieo_android_win_module
        PROJECT_TYPE module

        PACKAGES
            game-activity
            Arieo-Interface-Window
            Arieo-Core
        INTERFACES
            Arieo-Interface-Window::arieo_window_interface
        PRIVATE_LIBS
            Arieo-Core::arieo_core
            game-activity::game-activity_static
            android
            log
        
        SOURCES
            ${CMAKE_CURRENT_SOURCE_DIR}/private/src/*.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/private/src/*/*.cpp
    )
else()
    # Create a dummy install target for non-Android platforms
    message(STATUS "Arieo-Module-AndroidWindow: Skipping build for ${CMAKE_SYSTEM_NAME} (Android only)")
    install(CODE "message(STATUS \"Arieo-Module-AndroidWindow: No installation needed for ${CMAKE_SYSTEM_NAME}\")")
endif()