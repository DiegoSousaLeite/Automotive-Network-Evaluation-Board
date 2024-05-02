#ifndef ANALOGOUTPUTTEST_H
#define ANALOGOUTPUTTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class AnalogOutputTest : public GenericTest {
private:
    static AnalogOutputTest* instance;  // Declaração da instância singleton

    AnalogOutputTest();  // Construtor privado

public:
    static AnalogOutputTest* getInstance();  // Método de acesso ao singleton

    virtual ~AnalogOutputTest();  // Destruidor

    // Impedir cópia e atribuição
    AnalogOutputTest(const AnalogOutputTest&) = delete;
    AnalogOutputTest& operator=(const AnalogOutputTest&) = delete;
};

#endif // ANALOGOUTPUTTEST_H
