#ifndef PERSISTENCECONTROLLER_H
#define PERSISTENCECONTROLLER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMap>
#include "MCUFirmwareUpload.h"
#include "ecufirmwareupload.h"
#include "Board.h"
#include "Ecu1Board.h"
#include "Ecu2Board.h"
#include "Ecu3Board.h"
#include "Ecu4Board.h"
#include "Mcu1Board.h"
#include <libusb.h>
#include "SystemProperties.h"
#include "UtilsConversion.h"
#include <QThread>
#include <QRegularExpression>
#include <QProcess>
#include "CmdMessageConstants.h"

// Classe responsável pelo gerenciamento da persistência de dados e da comunicação com as placas (ECUs e MCU)
class PersistenceController : public QObject {
    Q_OBJECT

public:
    // Obtém a instância única da classe (Singleton)
    static PersistenceController* getInstance();
    virtual ~PersistenceController(); // Destrutor
    explicit PersistenceController(QObject *parent = nullptr); // Construtor

    // Métodos para carregar e manipular portas seriais
    int loadSerialCommPorts(); // Carrega as portas de comunicação serial
    QVector<SerialCommPort*> findSerialCommPorts(); // Encontra as portas de comunicação serial disponíveis
    QVector<SerialCommPort*> getSerialCommPortInfo(); // Obtém informações das portas de comunicação serial
    void setCommPortFound(int index, int commPortId); // Define uma porta de comunicação encontrada
    int getCommPortFound(int index) const; // Obtém uma porta de comunicação encontrada com base no índice

    // Métodos para manipulação do programador USB
    bool loadUsbProgrammer(); // Carrega o programador USB
    bool openConnection(int portId, int baudRate); // Abre uma conexão com uma porta serial específica
    bool openBoardConnection(int boardId, int baudRate); // Abre uma conexão com uma placa específica pelo boardId e baudRate
    bool openBoardConnection(int boardId); // Abre uma conexão com uma placa específica pelo boardId

    // Métodos para obter descrições e nomes das portas
    QString getSystemPortDescription(int index); // Obtém a descrição do sistema da porta com base no índice
    QString getPortDescription(int index); // Obtém a descrição da porta com base no índice
    QString getDescriptivePortName(int index); // Obtém o nome descritivo da porta com base no índice
    QString getBoardCommPort(int boardId); // Obtém a porta de comunicação da placa com base no boardId
    QString getBoardDescription(int boardId); // Obtém a descrição da placa com base no boardId
    int getTotalNumberOfPorts(); // Obtém o número total de portas disponíveis

    // Métodos para manipulação e leitura de dados da porta serial
    void serialWrite(int portId, const QString& atCmd, bool endOfLine); // Escreve um comando na porta serial especificada
    void serialBoardWrite(int boardId, const QString& atCmd, bool endOfLine); // Escreve um comando na placa especificada pelo boardId
    void closeConnection(int portId); // Fecha a conexão com a porta serial especificada
    void closeBoardConnection(int boardId); // Fecha a conexão com a placa especificada pelo boardId
    QString serialRead(int portId); // Lê dados da porta serial especificada
    QString serialBoardRead(int boardId); // Lê dados da placa especificada pelo boardId

    // Método para escrita de firmware na placa
    int writeFirmware(int testId, int boardId, const QString& cmdStr); // Escreve o firmware na placa especificada

    // Métodos para configuração e mensagens de teste
    void setBoardInformation(int portId, int boardId); // Configura as informações da placa com base no portId e boardId
    void addCmdTestMessage(int testId, int boardId, const QString& testMessage, bool header); // Adiciona uma mensagem de teste ao modelo
    void setReportProperty(const QString &key, const QString &value); // Define uma propriedade de relatório
    QString getReportProperty(const QString &key) const; // Obtém uma propriedade de relatório com base na chave

private:
    static PersistenceController* instance; // Instância única da classe (Singleton)
    libusb_context *usbContext = nullptr; // Contexto USB
    libusb_device* findUsbDevice(libusb_device** devices, uint16_t vid, uint16_t pid); // Encontra um dispositivo USB específico
    QVector<Board*> boardList; // Lista de objetos de placas (ECUs e MCU)
    MCUFirmwareUpload* mcuFwUpModel; // Modelo de upload de firmware para MCU
    ECUFirmwareUpload* ecuFwUpModel; // Modelo de upload de firmware para ECU
    libusb_device* usbDevice; // Dispositivo USB
    QVector<int> foundCommPorts; // Armazena os índices das portas encontradas
    QMap<QString, QString> reportProperties; // Propriedades de relatório
    QVector<QSerialPort*> serialComm; // Vetor de objetos QSerialPort para comunicação serial

    // Métodos encapsulados para acesso a serialComm
    QSerialPort* getSerialCommPort(int index); // Obtém a porta serial com base no índice
    void clearSerialComm(); // Limpa a lista de portas seriais
    void addSerialCommPort(QSerialPort* port); // Adiciona uma porta serial à lista
    int getSerialCommSize() const; // Obtém o tamanho da lista de portas seriais
};

#endif // PERSISTENCECONTROLLER_H
