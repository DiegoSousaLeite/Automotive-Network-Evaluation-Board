cmake_minimum_required(VERSION 3.5)

# Definir o nome do projeto
project(TestPersistenceController)

# Adicionar arquivos de origem
set(SOURCES
    ../PersistenceController.cpp
    ../SerialCommPort.cpp
    ../Board.cpp
    ../Ecu1Board.cpp
    ../Ecu2Board.cpp
    ../Ecu3Board.cpp
    ../Ecu4Board.cpp
    ../Mcu1Board.cpp
    ../ECUFirmwareUpload.cpp
    ../MCUFirmwareUpload.cpp
    ../GenericTest.cpp
    ../TestReportModel.cpp
    ../IndividualTest.cpp
    ../EcuBusinessController.cpp
    ../EcuFrameController.cpp
    ../FrameController.cpp
    ../RepBusinessController.cpp
    ../TimeOutMonitor.cpp
    ../McuBusinessController.cpp
    ../GetTestReport.cpp
    ../FindSerialPortTest.cpp
    ../CANInitTest.cpp
    ../LinNetworkTest.cpp
    ../AnalogInputTest.cpp
    ../CAN1NetworkTest.cpp
    ../CAN2NetworkTest.cpp
    ../CANLoopbackTest.cpp
    ../AnalogOutputTest.cpp
    ../DigitalInputTest.cpp
    ../MCUInterfaceTest.cpp
    ../CommunicationTest.cpp
    ../BusinessController.cpp
    test.cpp
)

# Adicionar cabeçalhos de inclusão
set(HEADERS
    ../SystemProperties.h
    ../EcuBusinessInterface.h
    ../McuBusinessInterface.h
    ../CmdMessageConstants.h
    ../JigaTestInterface.h
    ../AtCommandConstants.h
    ../Ecu1Board.h
    ../Ecu2Board.h
    ../Ecu3Board.h
    ../Ecu4Board.h
    ../Mcu1Board.h
    ../Board.h
    ../CommunicationTest.h
    ../DigitalInputTest.h
    ../AnalogInputTest.h
    ../AnalogOutputTest.h
    ../CANInitTest.h
    ../CANLoopbackTest.h
    ../CAN1NetworkTest.h
    ../CAN2NetworkTest.h
    ../LinNetworkTest.h
    ../MCUInterfaceTest.h
    ../PersistenceController.h
    ../FrameController.h
    ../ReportControllerInterface.h
    ../ErrorCodeInterface.h
    ../MenuOptionsInterface.h
    ../SystemBuilderInterface.h
    ../IFrameListener.h
    ../PropertyChangeListener.h
    ../ECUFirmwareUpload.h
    ../FindSerialPortTest.h
    ../UtilsConversion.h
    ../TimeOutListener.h
    ../TestReportModel.h
    ../IndividualTest.h
    ../GenericTest.h
    ../McuBusinessController.h
    ../RepBusinessController.h
    ../EcuBusinessController.h
    ../EcuFrameController.h
    ../GetTestReport.h
    ../SystemBuilder.h
    ../BusinessController.h
)


# Incluir diretórios
include_directories(${CMAKE_SOURCE_DIR})

# Linkar bibliotecas Qt e libusb
find_package(Qt6 REQUIRED COMPONENTS Core SerialPort)
find_library(LIBUSB_LIBRARY NAMES usb-1.0 libusb-1.0 PATHS /opt/homebrew/opt/libusb/lib REQUIRED)

# Incluindo diretórios da libusb
include_directories(SYSTEM /opt/homebrew/opt/libusb/include/libusb-1.0)

# Incluir Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Adicionar o executável de teste
add_executable(TestPersistenceController ${SOURCES})

# Linkando as bibliotecas ao executável
target_link_libraries(TestPersistenceController Qt6::Core Qt6::SerialPort ${LIBUSB_LIBRARY} ${GTEST_LIBRARIES} pthread)

# Adicionar teste
add_test(NAME TestPersistenceController COMMAND TestPersistenceController)

# Adicionar flags para o AddressSanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")

# Adicionar flags para o ThreadSanitizer
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -fno-omit-frame-pointer")
#set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=thread")
