cmake_minimum_required (VERSION 3.31)

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
        arieo::interface::window
    LIBS
        game-activity::game-activity_static
        arieo::base
        arieo::core
        android
        log
)
endif()