#ifndef ECUFIRMWAREUPLOAD_H
#define ECUFIRMWAREUPLOAD_H

#include "GenericTest.h"
#include <QList>
#include <QSharedPointer>
#include "TestReportModel.h"

class ECUFirmwareUpload : public GenericTest {
public:
    static ECUFirmwareUpload* getInstance();

private:
    ECUFirmwareUpload();
    static ECUFirmwareUpload* ecuFwUploadTestModel;
    QList<QSharedPointer<TestReportModel>> testReportModel;
};

#endif // ECUFIRMWAREUPLOAD_H
