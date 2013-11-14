project(plasma-autohidetoggleapplet)


cmake_minimum_required(VERSION 2.8)


find_package(KDE4 REQUIRED)
include(KDE4Defaults)

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(${CMAKE_SOURCE_DIR}  ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})

# src
add_subdirectory(src)

# translations
add_subdirectory(po)

# data
install(FILES plasma-applet-paneltoggle.desktop  DESTINATION ${SERVICES_INSTALL_DIR})

