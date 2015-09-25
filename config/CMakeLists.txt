qt5_wrap_ui(uic
    config.ui
)

add_executable(lxqt-config-appswitcher
    main.cpp
    config.h
    config.cpp
    ${uic}
)

target_link_libraries(lxqt-config-appswitcher
    Qt5::Core
    Qt5::Widgets
    lxqt
)

