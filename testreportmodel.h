#ifndef TESTREPORTMODEL_H
#define TESTREPORTMODEL_H

#include <QObject>
#include <QString>
#include <QList>
#include "individualtest.h"
#include <QVariant>


class TestReportModel : public QObject {
    Q_OBJECT

public:
    explicit TestReportModel(QObject *parent = nullptr);
    TestReportModel(int testId, int boardId, QObject *parent = nullptr);

    int getBoardID() const;
    void setBoardID(int boardId);

    int getTestID() const;
    void setTestID(int testId);

    QString getLastMessage() const;
    void addMessage(const QString &message);

    QString getBoardDescription() const;
    void resetReportModel();

    void addIndividualTest(int testId);
    void setTestResult(int testResult);
    void setIndividualTestResult(int testId, int testResult);
    int getIndividualTestResult(int testId) const;

    QString getFirstMessageAndRemove();

signals:
    void propertyChanged(const QString &property, const QVariant &oldValue, const QVariant &newValue);

private:
    int testId;
    int boardId;
    QList<QString> reportMsg;
    QList<IndividualTest> individuaTest;
};

#endif // TESTREPORTMODEL_H
