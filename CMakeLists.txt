cmake_minimum_required(VERSION 3.5)

project(ANEB_2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 COMPONENTS SerialPort REQUIRED)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ui_mainwindow.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ANEB_2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        ui_mainwindow.h
        virtual_io.h virtual_io.cpp virtual_io.ui
        ui_virtual_io.h
        AtCommandConstants.h
        CmdMessageConstants.h
        JigaTestInterface.h
        SystemProperties.h
        individualtest.h individualtest.cpp
        testreportmodel.h testreportmodel.cpp
        generictest.h generictest.cpp
        firmwareupload.h firmwareupload.cpp
        #ecuframecontroller.h ecuframecontroller.cpp
        serialcommport.h serialcommport.cpp
        EcuBusinessInterface.h
        Board.h
        Ecu1Board.h
        Environment.h
        Ecu2Board.h
        Ecu3Board.h
        Ecu4Board.h
        Mcu1Board.h
        ErrorCodeInterface.h
        AnalogInputTest.h
        AnalogOutputTest.h
        CAN1NetworkTest.h
        CAN2NetworkTest.h
        CANInitTest.h
        CommunicationTest.h
        DigitalInputTest.h
        SystemDefinition.h
        LinNetworkTest.h
        LoopbackCanTest.h
        MCUInterfaceTest.h
        ReportControllerInterface.h
    )

set(BUILD
    SystemDefinition.h
)

set(CONSTANTS_HEADERS
   CmdMessageConstants.h
   AtCommandConstants.h
   JigaTestInterface.h
   SystemProperties.h
   ErrorCodeInterface.h

)

set(MODEL
    testreportmodel.h testreportmodel.cpp
    serialcommport.h serialcommport.cpp

)

set(MODEL.TEST
    individualtest.h individualtest.cpp
    generictest.h generictest.cpp
    firmwareupload.h firmwareupload.cpp
    AnalogInputTest.h
    AnalogOutputTest.h
    CAN1NetworkTest.h
    CAN2NetworkTest.h
    CANInitTest.h
    CommunicationTest.h
    DigitalInputTest.h
    LinNetworkTest.h
    LoopbackCanTest.h
    MCUInterfaceTest.h
)

set(CONTROLLER
    ecuframecontroller.h ecuframecontroller.cpp

)

set(INTERFACE
    EcuBusinessInterface.h
    ReportControllerInterface.h
)


set(MODEL.BOARD
    Board.h
    Ecu1Board.h
    Ecu2Board.h
    Ecu3Board.h
    Ecu4Board.h
    Mcu1Board.h
)

source_group("Constants" FILES ${CONSTANTS_HEADERS})
source_group("Model" FILES ${MODEL})
source_group("Model.test" FILES ${MODEL.TEST})
source_group("Controller" FILES ${CONTROLLER})
source_group("Interface" FILES ${INTERFACE})
source_group("Model.board" FILES ${MODEL.BOARD})
source_group("Build" FILES ${BUILD})

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ANEB_2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ANEB_2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ANEB_2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ANEB_2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(ANEB_2 PRIVATE Qt6::SerialPort)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ANEB_2)
endif()
set_target_properties(ANEB_2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ANEB_2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ANEB_2)
endif()
