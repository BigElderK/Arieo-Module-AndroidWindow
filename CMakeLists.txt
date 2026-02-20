cmake_minimum_required (VERSION 3.31)

include($ENV{ARIEO_BUILD_ENV_PACKAGES_OUTPUT_DIR}/cmake/build_environment.cmake)
project(ArieoEngine)

# Only build for Android platforms
if(ARIEO_HOST_OS STREQUAL "android")
    # Check if game-activity is available before building
    find_package(game-activity QUIET)
    if(TARGET game-activity::game-activity_static)
        arieo_engine_project(
            arieo_android_win_module
            PROJECT_TYPE module

            DEPENDENCIES
                ARIEO_PACKAGES
                    Arieo-Core
                    Arieo-Interface-Window
                THIRDPARTY_PACKAGES
                    game-activity
                INTERFACES
                    Arieo-Interface-Window::arieo_window_interface
                PRIVATE_LIBS
                    Arieo-Core::arieo_core
                    game-activity::game-activity_static
                    android
                    log

            SOURCES
                CXX_SOURCES
                    ${CMAKE_CURRENT_LIST_DIR}/private/src/*.cpp
                    ${CMAKE_CURRENT_LIST_DIR}/private/src/*/*.cpp
        )
    else()
        # game-activity not available on Android platform
        message(STATUS "Arieo-Module-AndroidWindow: Skipping build - game-activity package not found")
        install(CODE "message(STATUS \"Arieo-Module-AndroidWindow: game-activity dependency not available\")")
    endif()
else()
    # Create a dummy install target for non-Android platforms
    message(STATUS "Arieo-Module-AndroidWindow: Skipping build for ${CMAKE_SYSTEM_NAME} (Android only)")
    install(CODE "message(STATUS \"Arieo-Module-AndroidWindow: No installation needed for ${CMAKE_SYSTEM_NAME}\")")
endif()
