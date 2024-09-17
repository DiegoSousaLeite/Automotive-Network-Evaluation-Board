#ifndef MCUBUSINESSCONTROLLER_H
#define MCUBUSINESSCONTROLLER_H

#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include "PersistenceController.h"
#include "JigaTestInterface.h"
#include "SystemProperties.h"
#include "CmdMessageConstants.h"
#include "EcuBusinessInterface.h"
#include "atCommandConstants.h"
#include "BusinessController.h"
#include <QSettings>
#include <QCoreApplication>
#include "McuBusinessInterface.h"
#include <stdexcept>

class McuBusinessController : public BusinessController{
    Q_OBJECT

public:
    explicit McuBusinessController(QObject *parent = nullptr);

    // Carrega o programador baseado no ID fornecido (serial ou USB).
    bool loadProgrammer(int programmerId);

    // Obtém o modo do programador serial.
    int getSerialProgrammerMode();

    // Define o modo do programador serial (programação ou serial).
    void setSerialProgrammerMode(int progMode);

    // Realiza o upload do firmware para o MCU utilizando o programador especificado.
    int uploadFirmware(int programmerId);

    // Configura a rede CAN Bus 1 para o MCU.
    bool setCanBus1Network();

    // Configura a rede CAN Bus 2 para o MCU (ainda não suportada).
    bool setCanBus2Network();

private:
    QSerialPort serialPort;  // Objeto para manipulação da porta serial.
    QTimer delayTimer;       // Temporizador para atrasos assíncronos.

    // Tenta carregar um programador USB.
    bool loadUsbProgrammer();

    // Tenta carregar um programador serial.
    bool loadSerialProgrammer();

protected:
    // Verifica a configuração da rede CAN Bus 1 para o teste especificado.
    int checkCanBus1Network(int testId);
};

#endif // MCUBUSINESSCONTROLLER_H
