#ifndef FIRMWAREUPLOAD_H
#define FIRMWAREUPLOAD_H

#include "GenericTest.h"
#include <QList>
#include <QSharedPointer>
#include "TestReportModel.h"
#include "IFrameListener.h"

class MCUFirmwareUpload : public GenericTest {
public:
    static MCUFirmwareUpload* getInstance();
    MCUFirmwareUpload();
    void addChangeListeners(IFrameListener* frameController);

private:

    static MCUFirmwareUpload* instance;
    QList<QSharedPointer<TestReportModel>> testReportModel;
    std::vector<IFrameListener*> listeners;
};

#endif // FIRMWAREUPLOAD_H
