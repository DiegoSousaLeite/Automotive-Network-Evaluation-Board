#ifndef MCUINTERFACETEST_H
#define MCUINTERFACETEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class MCUInterfaceTest : public GenericTest {
private:
    static MCUInterfaceTest* instance;  // Declaração da instância singleton

    MCUInterfaceTest();  // Construtor privado

public:
    virtual ~MCUInterfaceTest();  // Destruidor

    static MCUInterfaceTest* getInstance();  // Método de acesso ao singleton

    MCUInterfaceTest(const MCUInterfaceTest&) = delete;
    MCUInterfaceTest& operator=(const MCUInterfaceTest&) = delete;
};

#endif // MCUINTERFACETEST_H
