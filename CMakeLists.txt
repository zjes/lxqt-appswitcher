cmake_minimum_required(VERSION 2.8.11)
cmake_policy(VERSION 2.8)

project(lxqt-appswitcher)

find_package(Qt5 COMPONENTS Core Widgets)
find_package(lxqt)
find_package(lxqt-globalkeys REQUIRED)
find_package(KF5WindowSystem)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_definitions("-g -fPIC -Wall -Wextra -pedantic -Wformat=2 -Wnon-virtual-dtor -std=c++11 -Wl,--as-needed -z relro -z defs")

add_executable(${PROJECT_NAME}
    src/app-switcher.cpp
    src/app-switcher.h
    src/app-model.cpp
    src/app-model.h
    src/app-itemdelegate.cpp
    src/app-itemdelegate.h
    src/settings.h
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Widgets
    lxqt
    lxqt-globalkeys
)

add_subdirectory(config)
