#ifndef TESTREPORTMODEL_H
#define TESTREPORTMODEL_H

#include <QObject>
#include <QString>
#include <QList>
#include "IndividualTest.h"
#include <QVariant>
#include "PropertyChangeListener.h"
#include "SystemProperties.h"


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
    QString getLastMessageAndRemove();
    QString getFirstMessageAndRemove();

    QString getBoardDescription() const;
    void resetReportModel();

    void addChangeListeners(PropertyChangeListener* listener);
    void removeChangeListeners(PropertyChangeListener* listener);

    void addIndividualTest(int testId);
    void setTestResult(int testResult);
    void setIndividualTestResult(int testId, int testResult);
    int getIndividualTestResult(int testId) const;

    TestReportModel* getTestReportModel();



signals:


    void reportUpdated(const QString &message); // Sinal emitido quando um relatório é atualizado
    void reportRemoved(const QString &message); // Sinal emitido quando um relatório é removido

private:
    int testId;
    int boardId;
    QList<QString> reportMsg;
    QList<IndividualTest> individuaTest;

    QList<PropertyChangeListener*> listeners;

    void notifyPropertyChange(const QString &property, const QVariant &oldValue, const QVariant &newValue);
};

#endif // TESTREPORTMODEL_H
