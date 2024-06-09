#ifndef MCUFRAMECONTROLLER_H
#define MCUFRAMECONTROLLER_H

#include <QObject>
#include "FrameController.h"
#include "McuBusinessInterface.h"
#include "McuBusinessController.h"
#include "SystemProperties.h"

class McuFrameController : public FrameController {
    Q_OBJECT

public:
    explicit McuFrameController(QObject *parent = nullptr);
    virtual ~McuFrameController();

    void setMcuBusinessController(McuBusinessController* mcuInterface);

public slots:
    void executeFirmwareUpload(int programmer_id);
    void onPropertyChanged(const QString &property, const QVariant &value);

signals:
    void testMessageChanged(const QString &message);

private:
    McuBusinessController* bsController;
    FrameController* fwUpdateModel;
};

#endif // MCUFRAMECONTROLLER_H
