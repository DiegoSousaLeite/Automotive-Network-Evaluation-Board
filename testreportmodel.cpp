#include "TestReportModel.h"
#include "JigaTestInterface.h"

TestReportModel::TestReportModel(QObject *parent)
    : QObject(parent), testId(0), boardId(0) {
}

TestReportModel::TestReportModel(int testId, int boardId, QObject *parent)
    : QObject(parent), testId(testId), boardId(boardId) {
}

int TestReportModel::getBoardID() const {
    return boardId;
}

void TestReportModel::setBoardID(int boardId) {
    this->boardId = boardId;
}

int TestReportModel::getTestID() const {
    return testId;
}

void TestReportModel::setTestID(int testId) {
    this->testId = testId;
}

QString TestReportModel::getLastMessage() const {
    if (!reportMsg.isEmpty())
        return reportMsg.last();
    return QString();
}

void TestReportModel::addMessage(const QString &message) {
    QString oldMessage = getLastMessage();
    reportMsg.append(message);
    notifyPropertyChange(SystemProperties::TEST_MESSAGE_PROPERTY, oldMessage, message);
}

QString TestReportModel::getLastMessageAndRemove()
{
    if (!reportMsg.isEmpty()) {
        QString msg = reportMsg.last();
        reportMsg.removeLast();
        return msg;
    }
    return QString();
}

QString TestReportModel::getFirstMessageAndRemove() {
    if (!reportMsg.isEmpty()) {
        return reportMsg.takeFirst();  // Remove e retorna o primeiro elemento da lista
    }
    return QString();  // Retorna uma QString vazia se não houver mensagens
}

QString TestReportModel::getBoardDescription() const {

    switch (boardId) {
    case JigaTestInterface::ECU1_BOARD_ID:
        return "ECU1";
    case JigaTestInterface::ECU2_BOARD_ID:
        return "ECU2";
    case JigaTestInterface::ECU3_BOARD_ID:
        return "ECU3";
    case JigaTestInterface::ECU4_BOARD_ID:
        return "ECU4";
    case JigaTestInterface::MCU1_BOARD_ID:
        return "MCU1";
    default:
        return "Unknown";
    }
}

void TestReportModel::resetReportModel() {
    reportMsg.clear();
    for (IndividualTest &test : individuaTest) {
        test.resetTestResult();
    }
}

void TestReportModel::addChangeListeners(PropertyChangeListener *listener)
{
    if (!listeners.contains(listener)) {
        listeners.append(listener);
    }
}

void TestReportModel::removeChangeListeners(PropertyChangeListener *listener)
{
    listeners.removeAll(listener);
}

void TestReportModel::notifyPropertyChange(const QString &property, const QVariant &oldValue, const QVariant &newValue) {
    for (auto *listener : listeners) {
        listener->propertyChanged(property, oldValue, newValue);
    }
}

void TestReportModel::addIndividualTest(int testId) {
    individuaTest.append(IndividualTest(testId));
}

void TestReportModel::setTestResult(int testResult) {
    for (IndividualTest &test : individuaTest) {
        test.setTestResult(testResult);
    }
}

void TestReportModel::setIndividualTestResult(int testId, int testResult) {
    for (IndividualTest &test : individuaTest) {
        if (test.getTestId() == testId) {
            int oldResult = test.getTestResult();
            test.setTestResult(testResult);
           notifyPropertyChange("testResult", oldResult, testResult);
        }
    }
}

int TestReportModel::getIndividualTestResult(int testId) const {
    for (const IndividualTest &test : individuaTest) {
        if (test.getTestId() == testId) {
            return test.getTestResult();
        }
    }
    return -1;  // Indica um erro ou valor não encontrado.
}

TestReportModel* TestReportModel::getTestReportModel() {
    return this;
}



