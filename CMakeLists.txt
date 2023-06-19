cmake_minimum_required(VERSION 3.16...3.21)

# Change obs-plugintemplate to your plugin's name in a machine-readable format (e.g.: obs-myawesomeplugin) and set
project(obs-streamloots VERSION 2.0.0-rc.1)
add_library(${CMAKE_PROJECT_NAME} MODULE)

# Replace `Your Name Here` with the name (yours or your organization's) you want to see as the author of the plugin (in
# the plugin's metadata itself and in the installers)
set(PLUGIN_AUTHOR "Streamloots")

# Replace `com.example.obs-plugin-template` with a unique Bundle ID for macOS releases (used both in the installer and
# when submitting the installer for notarization)
set(MACOS_BUNDLEID "com.streamloots.obs-streamloots")

# Replace `me@contoso.com` with the maintainer email address you want to put in Linux packages
set(LINUX_MAINTAINER_EMAIL "engineering@streamloots.com")

# Add your custom source files here - header files are optional and only required for visibility e.g. in Xcode or Visual
# Studio
target_sources(
  ${CMAKE_PROJECT_NAME}
  PRIVATE src/plugin-main.cpp
          src/Config.cpp
          src/server/WSServer.cpp
          src/server/WSRequest.cpp
          src/use-case/DisplayImage.cpp
          src/use-case/DisplayVideo.cpp
          src/use-case/HideCamera.cpp
          src/use-case/PressKey.cpp
          src/use-case/RotateCamera.cpp
          src/use-case/UseCaseManager.cpp
          src/responses/Response.cpp
          src/responses/ResponseError.cpp
          src/requests/RequestTypes.cpp
          src/requests/RequestBase.cpp
          src/requests/DisplayImageRequest.cpp
          src/requests/DisplayVideoRequest.cpp
          src/requests/HideCameraRequest.cpp
          src/requests/PressKeyRequest.cpp
          src/requests/RotateCameraRequest.cpp
          src/forms/settings-dialog.cpp)

target_sources(
  ${CMAKE_PROJECT_NAME}
  PRIVATE src/plugin-macros.generated.h
          src/Config.hpp
          src/server/include/WSServer.h
          src/server/include/WSRequest.hpp
          src/use-case/include/DisplayImage.hpp
          src/use-case/include/DisplayVideo.hpp
          src/use-case/include/HideCamera.hpp
          src/use-case/include/PressKey.hpp
          src/use-case/include/RotateCamera.hpp
          src/use-case/include/UseCaseManager.hpp
          src/use-case//utils/getSceneItemInScene.hpp
          src/responses/include/Response.hpp
          src/responses/include/ResponseError.hpp
          src/requests/include/RequestTypes.hpp
          src/requests/include/RequestBase.hpp
          src/requests/include/DisplayImageRequest.hpp
          src/requests/include/DisplayVideoRequest.hpp
          src/requests/include/HideCameraRequest.hpp
          src/requests/include/PressKeyRequest.hpp
          src/requests/include/RotateCameraRequest.hpp
          src/requests/utils/metadata.hpp
          src/forms/settings-dialog.h)

# Import libobs as main plugin dependency
find_package(libobs REQUIRED)
include(cmake/ObsPluginHelpers.cmake)

# Uncomment these lines if you want to use the OBS Frontend API in your plugin
find_package(obs-frontend-api REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::obs-frontend-api)

# Uncomment those lines if you want to use Qt in your plugin
find_qt(COMPONENTS Widgets Core)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt::Core Qt::Widgets)
set_target_properties(
  ${CMAKE_PROJECT_NAME}
  PROPERTIES AUTOMOC ON
             AUTOUIC ON
             AUTORCC ON)

# Import asio

set(ASIO_DIR CACHE FILEPATH "ASIO_DIR library")

add_library(asio INTERFACE)
target_compile_definitions(asio INTERFACE ASIO_STANDALONE)
target_include_directories(asio SYSTEM INTERFACE "${ASIO_DIR}/asio/include")

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE asio)

# Import Websocketspp

set(CPPWS_DIR CACHE FILEPATH "CPPWS_DIR library")

add_library(Websockets INTERFACE)
target_include_directories(Websockets SYSTEM INTERFACE "${CPPWS_DIR}")

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Websockets)

# Import plugin pacros

configure_file(src/plugin-macros.h.in ${CMAKE_SOURCE_DIR}/src/plugin-macros.generated.h)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE src/plugin-macros.generated.h)

# /!\ TAKE NOTE: No need to edit things past this point /!\

# --- Platform-independent build settings ---

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::libobs)

# --- End of section ---

# --- Windows-specific build settings and tasks ---
if(OS_WINDOWS)
  configure_file(cmake/bundle/windows/installer-Windows.iss.in ${CMAKE_BINARY_DIR}/installer-Windows.generated.iss)

  configure_file(cmake/bundle/windows/resource.rc.in ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.rc)
  target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.rc)

  if(MSVC)
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /W4)
  endif()
  # --- End of section ---

  # -- macOS specific build settings and tasks --
elseif(OS_MACOS)
  configure_file(cmake/bundle/macos/installer-macos.pkgproj.in ${CMAKE_BINARY_DIR}/installer-macos.generated.pkgproj)

  set(MACOSX_PLUGIN_GUI_IDENTIFIER "${MACOS_BUNDLEID}")
  set(MACOSX_PLUGIN_BUNDLE_VERSION "${CMAKE_PROJECT_VERSION}")
  set(MACOSX_PLUGIN_SHORT_VERSION_STRING "1")

  target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall)
  # --- End of section ---

  # --- Linux-specific build settings and tasks ---
else()
  target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall)
endif()
# --- End of section ---

setup_plugin_target(${CMAKE_PROJECT_NAME})
