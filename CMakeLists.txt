cmake_minimum_required(VERSION 3.8.0)
cmake_policy(VERSION 3.8)

project(lxqt-appswitcher)
include(GNUInstallDirs)

find_package(Qt6 COMPONENTS Core Widgets)
find_package(lxqt)
find_package(lxqt-globalkeys REQUIRED)
find_package(KF6WindowSystem)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

option(UPDATE_TRANSLATIONS "Update source translation translations/*.ts files" OFF)

set(files
    src/app-switcher.cpp
    src/app-switcher.h
    src/app-model.cpp
    src/app-model.h
    src/app-itemdelegate.cpp
    src/app-itemdelegate.h
    src/settings.h
    src/main.cpp
)

include(LXQtTranslate)
lxqt_translate_ts(appswitcher-qm
    UPDATE_TRANSLATIONS ${UPDATE_TRANSLATIONS}
    SOURCES
        ${files}
    INSTALL_DIR
        "${LXQT_TRANSLATIONS_DIR}/${PROJECT_NAME}"
    COMPONENT runtime
)
lxqt_app_translation_loader(lxqt-appswitcher-qm ${PROJECT_NAME})

add_executable(${PROJECT_NAME}
    ${files}
    ${appswitcher-qm}
    ${lxqt-appswitcher-qm}
)

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Widgets
    lxqt
    lxqt-globalkeys
)

add_subdirectory(config)

install(TARGETS
    ${PROJECT_NAME}
    DESTINATION "${CMAKE_INSTALL_BINDIR}"
    COMPONENT runtime
)

install(FILES
    resources/lxqt-config-appswitcher.desktop
    DESTINATION "${LXQT_DATA_DIR}/applications"
)

install(FILES
    resources/lxqt-appswitcher.desktop
    DESTINATION "${LXQT_ETC_XDG_DIR}/autostart"
)

install(DIRECTORY
    resources/themes
    DESTINATION "${LXQT_SHARE_DIR}"
)
