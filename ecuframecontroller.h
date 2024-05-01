#ifndef ECUFRAMECONTROLLER_H
#define ECUFRAMECONTROLLER_H

#include <QObject>
#include <QString>
#include <QSerialPortInfo>


class EcuFrameController : public FrameController {
    Q_OBJECT

public:
    explicit EcuFrameController(QObject *parent = nullptr) : FrameController(parent) {
        connectSignals();
    }

    void executeTest(int testId, int boardId);

    void executeTest(int testId);

    void executeTestReport(int testId);

   void executeFirmwareUpload(int board_id);


signals:
    void modelPropertyChanged();

private:


    void connectSignals();
};

#endif // ECUFRAMECONTROLLER_H
