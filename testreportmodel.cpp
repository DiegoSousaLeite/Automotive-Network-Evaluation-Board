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
    int oldId = this->boardId;
    this->boardId = boardId;
    emit propertyChanged("boardId", oldId, boardId);
}

int TestReportModel::getTestID() const {
    return testId;
}

void TestReportModel::setTestID(int testId) {
    int oldId = this->testId;
    this->testId = testId;
    emit propertyChanged("testId", oldId, testId);
}

QString TestReportModel::getLastMessage() const {
    if (!reportMsg.isEmpty())
        return reportMsg.last();
    return QString();
}

void TestReportModel::addMessage(const QString &message) {
    QString oldMessage = getLastMessage();
    reportMsg.append(message);
    emit propertyChanged("message", oldMessage, message);
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
    case JigaTestConstants::ECU1_BOARD_ID:
        return "ECU1";
    case JigaTestConstants::ECU2_BOARD_ID:
        return "ECU2";
    case JigaTestConstants::ECU3_BOARD_ID:
        return "ECU3";
    case JigaTestConstants::ECU4_BOARD_ID:
        return "ECU4";
    case JigaTestConstants::MCU1_BOARD_ID:
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
            emit propertyChanged("testResult", oldResult, testResult);
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

void TestReportModel::notifyPropertyChange(const QString &property, const QVariant &oldValue, const QVariant &newValue) {
    emit propertyChanged(property, oldValue, newValue);
}

