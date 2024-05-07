#ifndef ANALOGINPUTTEST_H
#define ANALOGINPUTTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"


class AnalogInputTest : public GenericTest {
private:
    static AnalogInputTest* instance;  // Singleton instance

    // Construtor privado
    AnalogInputTest();

public:
    // Singleton Access
    static AnalogInputTest* getInstance();

    // Destructor
    virtual ~AnalogInputTest();

    // Evita a cópia e atribuição
    AnalogInputTest(const AnalogInputTest&) = delete;
    AnalogInputTest& operator=(const AnalogInputTest&) = delete;
};

#endif // ANALOGINPUTTEST_H
