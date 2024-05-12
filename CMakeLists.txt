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
        IndividualTest.h IndividualTest.cpp
        TestReportModel.h TestReportModel.cpp
        GenericTest.h GenericTest.cpp
        FirmwareUpload.h FirmwareUpload.cpp
        EcuFrameController.h EcuFrameController.cpp
        SerialCommPort.h SerialCommPort.cpp
        EcuBusinessInterface.h
        Board.h
        Ecu1Board.h Ecu1Board.cpp
        Environment.h
        Ecu2Board.h Ecu2Board.cpp
        Ecu3Board.h Ecu3Board.cpp
        Ecu4Board.h Ecu4Board.cpp
        Mcu1Board.h Mcu1Board.cpp
        ErrorCodeInterface.h
        AnalogInputTest.h AnalogInputTest.cpp
        AnalogOutputTest.h AnalogOutputTest.cpp
        CAN1NetworkTest.h CAN1NetworkTest.cpp
        CAN2NetworkTest.h CAN2NetworkTest.cpp
        CANInitTest.h CANInitTest.cpp
        CommunicationTest.h CommunicationTest.cpp
        DigitalInputTest.h DigitalInputTest.cpp
        SystemDefinition.h
        LinNetworkTest.h  LinNetworkTest.cpp
        LoopbackCanTest.h LoopbackCanTest.cpp
        MCUInterfaceTest.h  MCUInterfaceTest.cpp
        ReportControllerInterface.h
        FrameController.h FrameController.cpp
        McuFrameController.h McuFrameController.cpp
        McuBusinessInterface.h
        PersistenceController.h PersistenceController.cpp
        UtilsConversion.h
        BusinessController.h BusinessController.cpp
        RepBusinessController.h RepBusinessController.cpp
        TimeOutMonitor.h TimeOutMonitor.cpp
        TimeOutListener.h
        McuBusinessController.h McuBusinessController.cpp
        MenuOptionsInterface.h
        SystemBuilderInterface.h
        GetTestReport.h GetTestReport.cpp
        #EcuBusinessController.h EcuBusinessController.cpp






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
   MenuOptionsInterface.h

)

set(MODEL
    TestReportModel.h TestReportModel.cpp
    SerialCommPort.h SerialCommPort.cpp
    TimeOutMonitor.h TimeOutMonitor.cpp
    GetTestReport.h GetTestReport.cpp

)

set(MODEL_TEST
    IndividualTest.h IndividualTest.cpp
    GenericTest.h GenericTest.cpp
    FirmwareUpload.h FirmwareUpload.cpp
    AnalogInputTest.h AnalogInputTest.cpp
    AnalogOutputTest.h AnalogOutputTest.cpp
    CAN1NetworkTest.h CAN1NetworkTest.cpp
    CAN2NetworkTest.h CAN2NetworkTest.cpp
    CANInitTest.h CANInitTest.cpp
    CommunicationTest.h  CommunicationTest.cpp
    DigitalInputTest.h DigitalInputTest.cpp
    LinNetworkTest.h LinNetworkTest.cpp
    LoopbackCanTest.h LoopbackCanTest.cpp
    MCUInterfaceTest.h  MCUInterfaceTest.cpp
)

set(CONTROLLER
    EcuFrameController.h EcuFrameController.cpp
    FrameController.h FrameController.cpp
    McuFrameController.h McuFrameController.cpp

)

set(CONTROLLER_BUSINESS
    BusinessController.h BusinessController.cpp
    #EcuBusinessController.h EcuBusinessController.cpp
    RepBusinessController.h RepBusinessController.cpp
    McuBusinessController.h McuBusinessController.cpp
)

set(CONTROLLER_PERSISTENCE
    PersistenceController.h PersistenceController.cpp
)

set(INTERFACE
    EcuBusinessInterface.h
    ReportControllerInterface.h
    McuBusinessInterface.h
    TimeOutListener.h
    SystemBuilderInterface.h
)


set(MODEL_BOARD
    Board.h
    Ecu1Board.h Ecu1Board.cpp
    Ecu2Board.h Ecu2Board.cpp
    Ecu3Board.h Ecu3Board.cpp
    Ecu4Board.h Ecu4Board.cpp
    Mcu1Board.h Mcu1Board.cpp
)

source_group("Constants" FILES ${CONSTANTS_HEADERS})
source_group("Model" FILES ${MODEL})
source_group("Model_test" FILES ${MODEL_TEST})
source_group("Controller" FILES ${CONTROLLER})
source_group("Controller_business" FILES ${CONTROLLER_BUSINESS})
source_group("Controller_persistence" FILES ${CONTROLLER_PERSISTENCE})
source_group("Interface" FILES ${INTERFACE})
source_group("Model_board" FILES ${MODEL_BOARD})
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

# Primeiro, encontrando a biblioteca libusb
find_library(LIBUSB_LIBRARY NAMES usb-1.0 libusb-1.0 PATHS /opt/homebrew/opt/libusb/lib REQUIRED)

# Incluindo diretórios da libusb
include_directories(SYSTEM /opt/homebrew/opt/libusb/include/libusb-1.0)

# Linkando as bibliotecas ao executável
target_link_libraries(ANEB_2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::SerialPort ${LIBUSB_LIBRARY})


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
