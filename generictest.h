#ifndef GENERICTEST_H
#define GENERICTEST_H

#include <QObject>
#include <QList>
#include "TestReportModel.h"
#include "JigaTestInterface.h"
//#include "FrameController.h"

//class FrameController;

class GenericTest : public QObject {
    Q_OBJECT

public:
    GenericTest(QObject *parent = nullptr);

    QList<TestReportModel*> getTestReports() const;
    TestReportModel* getTestReport(int boardId) const;
    int getSize() const;

    void setTestResult(int boardId, int testResult);
    void addTestMessage(int boardId, const QString &message);
    void addTestMessage(const QString &message);

    void setIndividualTestResult(int boardId, int testId, int testResult);
    int getIndividualTestResult(int boardId, int testId) const;

    QString getLastMessage(int boardId) const;
    QString getMessageAndRemove(int boardId);

    QString getBoardDescription(int boardId) const;

    void resetTestModel();
    QList<TestReportModel*> testReportModel;

   // void addChangeListeners(FrameController frameController);
   // void removeChangeListeners(FrameController frameController);

private:

};

#endif // GENERICTEST_H
