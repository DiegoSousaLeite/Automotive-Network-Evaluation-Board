#ifndef MCUFRAMECONTROLLER_H
#define MCUFRAMECONTROLLER_H

#include <QObject>
#include "FrameController.h"
#include "McuBusinessInterface.h"
#include "McuBusinessController.h"
#include "SystemProperties.h"

// McuFrameController é uma classe derivada de FrameController que lida com operações relacionadas à MCU (Unidade de Controle Microcontrolada).
class McuFrameController : public FrameController {
    Q_OBJECT

public:
    explicit McuFrameController(QObject *parent = nullptr); // Construtor que inicializa o controlador de quadro para MCU
    virtual ~McuFrameController(); // Destrutor para liberar recursos

    // Define o controlador de negócios da MCU, responsável pelas operações relacionadas à MCU
    void setMcuBusinessController(McuBusinessController* mcuInterface);

public slots:
    // Executa o upload do firmware usando o programador especificado pelo ID
    void executeFirmwareUpload(int programmer_id);
    // Slot que é chamado quando uma propriedade do sistema é alterada
    void onPropertyChanged(const QString &property, const QVariant &value);

signals:
    // Sinal emitido quando uma mensagem de teste é alterada
    void testMessageChanged(const QString &message);

private:
    McuBusinessController* bsController; // Ponteiro para o controlador de negócios da MCU
};

#endif // MCUFRAMECONTROLLER_H
