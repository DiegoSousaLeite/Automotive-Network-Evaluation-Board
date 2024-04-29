#include "generictest.h"

GenericTest::GenericTest(QObject *parent) : QObject(parent) {
}

QList<TestReportModel*> GenericTest::getTestReports() const {
    return testReportModels;
}

TestReportModel* GenericTest::getTestReport(int boardId) const {
    for (TestReportModel* model : testReportModels) {
        if (model->getBoardID() == boardId) {
            return model;
        }
    }
    return nullptr;
}

int GenericTest::getSize() const {
    return testReportModels.size();
}

void GenericTest::setTestResult(int boardId, int testResult) {
    TestReportModel* model = getTestReport(boardId);
    if (model) {
        model->setTestResult(testResult);
    }
}

void GenericTest::addTestMessage(int boardId, const QString &message) {
    TestReportModel* model = getTestReport(boardId);
    if (model) {
        model->addMessage(message);
    }
}

void GenericTest::addTestMessage(const QString &message) {
    for (TestReportModel* model : testReportModels) {
        model->addMessage(message);
    }
}

void GenericTest::setIndividualTestResult(int boardId, int testId, int testResult) {
    TestReportModel* model = getTestReport(boardId);
    if (model) {
        model->setIndividualTestResult(testId, testResult);
    }
}

int GenericTest::getIndividualTestResult(int boardId, int testId) const {
    TestReportModel* model = getTestReport(boardId);
    if (model) {
        return model->getIndividualTestResult(testId);
    }
    return JigaTestConstants::ERROR_TO_EXECUTE_TEST;
}

QString GenericTest::getLastMessage(int boardId) const {
    TestReportModel* model = getTestReport(boardId);
    if (model) {
        return model->getLastMessage();
    }
    return QString();
}

QString GenericTest::getMessageAndRemove(int boardId) {
    TestReportModel* model = getTestReport(boardId);
    if (model) {
        return model->getFirstMessageAndRemove();
    }
    return QString();
}

QString GenericTest::getBoardDescription(int boardId) const {
    TestReportModel* model = getTestReport(boardId);
    if (model) {
        return model->getBoardDescription();
    }
    return "Unknown";
}


void GenericTest::resetTestModel() {
    for (TestReportModel* model : testReportModels) {
        model->resetReportModel();
    }
}
