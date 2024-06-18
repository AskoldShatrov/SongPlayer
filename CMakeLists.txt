cmake_minimum_required(VERSION 3.16)

project(SongPlayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick Multimedia)


qt_add_executable(appSongPlayer
    sources/main.cpp
    sources/PlayerController.cpp
    sources/PlayerController.h


)

qt_add_qml_module(appSongPlayer
    URI SongPlayer
    VERSION 1.0
    QML_FILES
    main.qml
    SearchField.qml
    SearchPanel.qml
    PlaylistPanel.qml
    ImageButton.qml
    AudioInfoBox.qml
    CustomSlider.qml

        SOURCES
        sources/AudioInfo.cpp
        sources/AudioInfo.h
        sources/audiosearchmodel.cpp
        sources/audiosearchmodel.h

        RESOURCES
        assets/icons/app_icon.png
        assets/icons/pause_icon.png
        assets/icons/play_icon.png
        assets/icons/prev_icon.png
        assets/icons/next_icon.png
        assets/icons/add_icon.png
        assets/icons/menu_icon.png
        assets/icons/trash_icon.png
        assets/icons/search_icon.png
        assets/icons/close_icon.png
        assets/icons/top_icon.png

        assets/images/song1jpg.jpg
        assets/images/song2.jpg

        RESOURCES
        assets/audio/mmm.mp3
        assets/audio/mmmm.mp3
        assets/videos/mmm.mp4

    )

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSongPlayer PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSongPlayer
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSongPlayer
    PRIVATE Qt6::Quick Qt6::Multimedia
)

include(GNUInstallDirs)
install(TARGETS appSongPlayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
