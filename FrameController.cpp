#include "FrameController.h"
#include <QTimer>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(lcFrameController, "controller.frame")

// Construtor da classe FrameController
FrameController::FrameController(QObject *parent) : QObject(parent) {
    // Inicialização dos modelos de teste
    commTestModel   = CommunicationTest::getInstance();
    diInputModel    = DigitalInputTest::getInstance();
    anInputModel    = AnalogInputTest::getInstance();
    anOutputModel   = AnalogOutputTest::getInstance();
    canInitModel    = CANInitTest::getInstance();
    lbNetworkModel  = CANLoopbackTest::getInstance();
    c1NetworkModel  = CAN1NetworkTest::getInstance();
    c2NetworkModel  = CAN2NetworkTest::getInstance();
    lnNetworkModel  = LinNetworkTest::getInstance();
    ecuFwUpModel    = ECUFirmwareUpload::getInstance();
    mcuFwUpModel    = MCUFirmwareUpload::getInstance();
    mcu1TestModel   = MCUInterfaceTest::getInstance();
    findSerialModel = FindSerialPortTest::getInstance();
}

FrameController::~FrameController() {
    // Destruição apropriada, se necessário
}

// Adiciona um listener para mudanças nos testes
void FrameController::addChangeListener(IFrameListener *listener)
{
    if (!listeners.contains(listener)) {
        listeners.append(listener);
    }
}

// Remove um listener para mudanças nos testes
void FrameController::removeChangeListener(IFrameListener *listener)
{
    listeners.removeAll(listener);
}

// Reseta o modelo de teste baseado no ID do teste
void FrameController::resetTestModel(int test_id) {
    qDebug() << "resetTest rodou";
    switch (test_id) {
    case JigaTestInterface::COMMUNICATION_TEST:
        commTestModel->resetTestModel();
        break;
    case JigaTestInterface::DIGITAL_INPUT_TEST:
        diInputModel->resetTestModel();
        break;
    case JigaTestInterface::ANALOG_INPUT_TEST:
        anInputModel->resetTestModel();
        break;
    case JigaTestInterface::ANALOG_OUTPUT_TEST:
        anOutputModel->resetTestModel();
        break;
    case JigaTestInterface::CAN_INIT_TEST:
        canInitModel->resetTestModel();
        break;
    case JigaTestInterface::CAN_LOOPBACK_TEST:
        lbNetworkModel->resetTestModel();
        break;
    case JigaTestInterface::CAN1_NETWORK_TEST:
        c1NetworkModel->resetTestModel();
        break;
    case JigaTestInterface::CAN2_NETWORK_TEST:
        c2NetworkModel->resetTestModel();
        break;
    case JigaTestInterface::LIN_NETWORK_TEST:
        lnNetworkModel->resetTestModel();
        break;
    case JigaTestInterface::ECU_FIRMWARE_UPLOAD:
        ecuFwUpModel->resetTestModel();
        break;
    case JigaTestInterface::MCU_FIRMWARE_UPLOAD:
        mcuFwUpModel->resetTestModel();
        break;
    case JigaTestInterface::MCU_RST_ACT_TEST:
    case JigaTestInterface::MCU_RST_DAC_TEST:
    case JigaTestInterface::MCU_IDENT_PORT_TEST:
    case JigaTestInterface::MCU_SEL_CANBUS1_TEST:
    case JigaTestInterface::MCU_SEL_CANBUS2_TEST: {
        mcu1TestModel->resetTestModel();
        break;
    }
    case JigaTestInterface::FIND_SERIAL_PORT_TEST:
        findSerialModel->resetTestModel();
        break;
    default:
        break;
    }
}

// Adiciona uma mensagem de cabeçalho ao relatório de teste com base no ID do teste e da placa
void FrameController::addHeaderTestMessage(int test_id, int board_id, const QString &testMessage) {
    QString strMessage;

    switch(test_id) {
    case JigaTestInterface::COMMUNICATION_TEST:
        strMessage = QString("%1 %2%3").arg(CmdMessageConstants::CMD_HDR_COMMUNICATION)
                         .arg(CmdMessageConstants::CMD_MSG_COMMUNICATION)
                         .arg(testMessage);
        commTestModel->addTestMessage(board_id, strMessage);
        break;

    case JigaTestInterface::DIGITAL_INPUT_TEST:
        strMessage = QString("%1 %2%3").arg(CmdMessageConstants::CMD_HDR_DIGITAL_INPUT)
                         .arg(CmdMessageConstants::CMD_MSG_DIGITAL_INPUT)
                         .arg(testMessage);
        diInputModel->addTestMessage(board_id, strMessage);
        break;

    case JigaTestInterface::ANALOG_INPUT_TEST:
        strMessage = QString("%1 %2%3").arg(CmdMessageConstants::CMD_HDR_ANALOG_INPUT)
                         .arg(CmdMessageConstants::CMD_MSG_ANALOG_INPUT)
                         .arg(testMessage);
        anInputModel->addTestMessage(board_id, strMessage);
        break;

    case JigaTestInterface::ANALOG_OUTPUT_TEST:
        strMessage = QString("%1 %2%3").arg(CmdMessageConstants::CMD_HDR_ANALOG_OUTPUT)
                         .arg(CmdMessageConstants::CMD_MSG_ANALOG_OUTPUT)
                         .arg(testMessage);
        anOutputModel->addTestMessage(board_id, strMessage);
        break;

    case JigaTestInterface::CAN_INIT_TEST:
        strMessage = QString("%1 %2%3").arg(CmdMessageConstants::CMD_HDR_CAN_INIT)
                         .arg(CmdMessageConstants::CMD_MSG_CAN_INIT)
                         .arg(testMessage);
        canInitModel->addTestMessage(board_id, strMessage);
        break;

    case JigaTestInterface::CAN_LOOPBACK_TEST:
        strMessage = QString("%1 %2%3").arg(CmdMessageConstants::CMD_HDR_LOOPBACK_CAN)
                         .arg(CmdMessageConstants::CMD_MSG_LOOPBACK_CAN)
                         .arg(testMessage);
        lbNetworkModel->addTestMessage(board_id, strMessage);
        break;

    case JigaTestInterface::CAN1_NETWORK_TEST:
        strMessage = QString("%1 %2%3").arg(CmdMessageConstants::CMD_HDR_CAN1_NETWORK)
                         .arg(CmdMessageConstants::CMD_MSG_CAN1_NETWORK)
                         .arg(testMessage);
        c1NetworkModel->addTestMessage(board_id, strMessage);
        break;

    case JigaTestInterface::CAN2_NETWORK_TEST:
        strMessage = QString("%1 %2%3").arg(CmdMessageConstants::CMD_HDR_CAN2_NETWORK)
                         .arg(CmdMessageConstants::CMD_MSG_CAN2_NETWORK)
                         .arg(testMessage);
        c2NetworkModel->addTestMessage(board_id, strMessage);
        break;

    case JigaTestInterface::LIN_NETWORK_TEST:
        strMessage = QString("%1 %2%3").arg(CmdMessageConstants::CMD_HDR_LIN_NETWORK)
                         .arg(CmdMessageConstants::CMD_MSG_LIN_NETWORK)
                         .arg(testMessage);
        lnNetworkModel->addTestMessage(board_id, strMessage);
        break;

    case JigaTestInterface::ECU_FIRMWARE_UPLOAD:
        strMessage = QString("%1 %2%3").arg(CmdMessageConstants::CMD_HDR_FIRM_UPLOAD)
                         .arg(CmdMessageConstants::CMD_MSG_FIRM_UPDATE)
                         .arg(testMessage);
        ecuFwUpModel->addTestMessage(board_id, strMessage);
        break;

    case JigaTestInterface::MCU_FIRMWARE_UPLOAD:
        strMessage = QString("%1 %2%3").arg(CmdMessageConstants::CMD_HDR_FIRM_UPLOAD)
                         .arg(CmdMessageConstants::CMD_MSG_FIRM_UPDATE)
                         .arg(testMessage);
        mcuFwUpModel->addTestMessage(board_id, strMessage);
        break;

    case JigaTestInterface::MCU_RST_ACT_TEST:
    case JigaTestInterface::MCU_RST_DAC_TEST:
    case JigaTestInterface::MCU_RST_ATT_TEST:
    case JigaTestInterface::MCU_IDENT_PORT_TEST:
    case JigaTestInterface::MCU_SEL_CANBUS1_TEST:
    case JigaTestInterface::MCU_SEL_CANBUS2_TEST:
        strMessage = QString("%1 %2%3").arg(CmdMessageConstants::CMD_HDR_MCU_INTERFACE)
                         .arg(CmdMessageConstants::CMD_MSG_MCU_INTERFACE)
                         .arg(testMessage);
        mcu1TestModel->addTestMessage(board_id, strMessage);
        break;

    case JigaTestInterface::FIND_SERIAL_PORT_TEST:
        strMessage = QString("%1 %2%3").arg(CmdMessageConstants::CMD_HDR_FIND_SERIAL_PORT)
                         .arg(CmdMessageConstants::CMD_MSG_MCU_INTERFACE)
                         .arg(testMessage);
        findSerialModel->addTestMessage(board_id, strMessage);
        break;
    }
}

// Aguarda o tempo limite para relatórios de teste com base no ID do teste e offset
void FrameController::waitReportTestTimeout(int test_id, int offset) {
    int timeOut = 0;

    // Alguns testes específicos não precisam de timeout, saindo imediatamente
    if (test_id == JigaTestInterface::COMMUNICATION_TEST || test_id == JigaTestInterface::CAN_INIT_TEST) {
        return;
    }

    // Define o tempo limite com base no tipo de teste
    switch(test_id) {
    case JigaTestInterface::DIGITAL_INPUT_TEST:
        timeOut = JigaTestInterface::DIGITAL_INPUT_TEST_TIMEOUT + offset;
        break;
    case JigaTestInterface::ANALOG_INPUT_TEST:
        timeOut = JigaTestInterface::ANALOG_INPUT_TEST_TIMEOUT + offset;
        break;
    case JigaTestInterface::ANALOG_OUTPUT_TEST:
        timeOut = JigaTestInterface::ANALOG_OUTPUT_TEST_TIMEOUT + offset;
        break;
    case JigaTestInterface::CAN_INIT_TEST:
    case JigaTestInterface::CAN_LOOPBACK_TEST:
    case JigaTestInterface::CAN1_NETWORK_TEST:
    case JigaTestInterface::CAN2_NETWORK_TEST: {
        timeOut = JigaTestInterface::CAN_NETWORK_TEST_TIMEOUT + offset;
        break;
    }
    case JigaTestInterface::LIN_NETWORK_TEST:
        timeOut = JigaTestInterface::LIN_NETWORK_TEST_TIMEOUT + offset;
        break;
    case JigaTestInterface::MCU_GET_CANBUS_TEST:
        timeOut = JigaTestInterface::MCU_CANBUS_TEST_TIMEOUT + offset;
        break;
    default:
        qDebug() << "Unknown test ID:" << test_id;
        return;
    }

    // Configura um timer para disparar uma ação após o tempo limite
    if (timeOut > 0) {
        QTimer::singleShot(timeOut * 1000, this, SLOT(handleTimeout()));
    }
}

// Slot chamado quando ocorre um timeout
void FrameController::handleTimeout()
{
    qDebug() << "Timeout occurred";
}

// Define o controlador de relatórios
void FrameController::setReportController(RepBusinessController *rpController) {
    this->rpController = rpController;
}

// Adiciona modelos de relatório de teste e conecta seus sinais de atualização
void FrameController::addTestReportModels(const QList<TestReportModel*>& models) {
    for (TestReportModel* model : models) {
        connect(model, &TestReportModel::reportUpdated, this, &FrameController::onReportUpdated);
    }
}

// Slot chamado quando um relatório de teste é atualizado
void FrameController::onReportUpdated(const QString &message) {
    qDebug() << "Received update from TestReportModel:" << message;
}
