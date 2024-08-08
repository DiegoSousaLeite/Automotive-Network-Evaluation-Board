#ifndef FINDSERIALPORTTEST_H
#define FINDSERIALPORTTEST_H

#include "GenericTest.h"
#include <QList>
#include <QSharedPointer>
#include "TestReportModel.h"

class FindSerialPortTest : public GenericTest {
public:
    static FindSerialPortTest* getInstance();

private:
    FindSerialPortTest();
    static FindSerialPortTest* findSerialTestModel;
    QList<QSharedPointer<TestReportModel>> testReportModel;
};

#endif // FINDSERIALPORTTEST_H
