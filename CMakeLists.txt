cmake_minimum_required(VERSION 3.16)

project(IIspaceProxy VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(authen)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network Core)
find_package(Qt${QT_VERSION_MAJOR}keychain CONFIG REQUIRED)

include_directories(${QTKEYCHAIN_INCLUDE_DIRS})

if(QT_FEATURE_static)
    set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded)
endif ()

set(PROJECT_SOURCES
        main.cpp
        space.cpp space.h space.ui
        reqmon.ui reqmon.h reqmon.cpp
        apirequest.h apirequest.cpp
        storage.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(IIspaceProxy
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
else()
    add_executable(IIspaceProxy
            ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(IIspaceProxy PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network
        $<IF:$<BOOL:${APPLE}>, Qt${QT_VERSION_MAJOR}keychain, Qt6Keychain::Qt6Keychain>
        authen
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for macOS, you should consider setting an
# explicit, fixed bundle identifier manually.
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.IIspaceProxy)
endif()
set_target_properties(IIspaceProxy PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)



########################## Install ###########################
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/deploy)

if(APPLE)
    install(TARGETS IIspaceProxy
            BUNDLE DESTINATION .
            )
    install(TARGETS authen LIBRARY DESTINATION ${PROJECT_NAME}.app/Contents/Frameworks)
    set_target_properties(authen PROPERTIES INSTALL_RPATH "@executable_path/../Frameworks")
else()
    install(TARGETS IIspaceProxy
            RUNTIME DESTINATION .)
    install(TARGETS authen RUNTIME DESTINATION .)
endif ()

if(QT_FEATURE_shared)
qt_generate_deploy_app_script(
        TARGET IIspaceProxy
        OUTPUT_SCRIPT deploy_script
)
install(SCRIPT ${deploy_script})
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(IIspaceProxy)
endif()