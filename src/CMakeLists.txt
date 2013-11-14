set(SRCS applet.cpp config/generalconfig.cpp config/appearanceconfig.cpp config/configpage.cpp config/config.cpp)
kde4_add_ui_files(SRCS ui/generalconfig.ui ui/appearanceconfig.ui)


kde4_add_plugin(plasma_applet_paneltoggle ${SRCS})
target_link_libraries(plasma_applet_paneltoggle ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS})
 
install(TARGETS plasma_applet_paneltoggle DESTINATION ${PLUGIN_INSTALL_DIR})
