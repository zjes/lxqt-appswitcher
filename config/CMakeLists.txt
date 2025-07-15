qt6_wrap_ui(uic
    config.ui
)

set(files
    main.cpp
    config.h
    config.cpp
    ${uic}
)

include(LXQtTranslate)

lxqt_translate_ts(qm_conf
    UPDATE_TRANSLATIONS
        ${UPDATE_TRANSLATIONS}
    SOURCES
        ${files}
    TEMPLATE
        lxqt-config-appswitcher
    INSTALL_DIR
        "${LXQT_TRANSLATIONS_DIR}/lxqt-config-appswitcher"
    COMPONENT runtime
)
lxqt_app_translation_loader(lxqt-config-qm lxqt-config-appswitcher)

add_executable(lxqt-config-appswitcher
    ${files}
    ${qm_conf}
    ${lxqt-config-qm}
)

target_link_libraries(lxqt-config-appswitcher
    Qt6::Core
    Qt6::Widgets
    lxqt
)

install(TARGETS
    lxqt-config-appswitcher
    DESTINATION "${CMAKE_INSTALL_BINDIR}"
)
