#ifndef INDIVIDUALTEST_H
#define INDIVIDUALTEST_H

class IndividualTest {
public:
    // Define os códigos de erro ou outros resultados relevantes como constantes estáticas.
    static const int ERROR_TO_EXECUTE_TEST = -1;

    IndividualTest(int testID);

    int getTestId() const;
    void setTestId(int testId);

    int getTestResult() const;
    void setTestResult(int testResult);

    void resetTestResult();

private:
    int testId;
    int testResult;
};

#endif // INDIVIDUALTEST_H
