#ifndef DIGITALINPUTTEST_H
#define DIGITALINPUTTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class DigitalInputTest : public GenericTest {
private:
    static DigitalInputTest* instance;  // Declaração da instância singleton

    DigitalInputTest();  // Construtor privado

public:
    static DigitalInputTest* getInstance();  // Método de acesso ao singleton

    virtual ~DigitalInputTest();  // Destruidor

    // Impedir cópia e atribuição
    DigitalInputTest(const DigitalInputTest&) = delete;
    DigitalInputTest& operator=(const DigitalInputTest&) = delete;
};

#endif // DIGITALINPUTTEST_H
