#include "individualtest.h"

IndividualTest::IndividualTest(int testID)
    : testId(testID), testResult(ERROR_TO_EXECUTE_TEST) {
    // Constructor initialization
}

int IndividualTest::getTestId() const {
    return testId;
}

void IndividualTest::setTestId(int testId) {
    this->testId = testId;
}

int IndividualTest::getTestResult() const {
    return testResult;
}

void IndividualTest::setTestResult(int testResult) {
    this->testResult = testResult;
}

void IndividualTest::resetTestResult() {
    this->testResult = ERROR_TO_EXECUTE_TEST;
}
