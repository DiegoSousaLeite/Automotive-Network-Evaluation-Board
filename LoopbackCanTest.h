#ifndef LOOPBACKCANTEST_H
#define LOOPBACKCANTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class LoopbackCanTest : public GenericTest {
private:
    static LoopbackCanTest* instance;  // Declaração da instância singleton

    LoopbackCanTest();  // Construtor privado

public:
    virtual ~LoopbackCanTest();  // Destruidor

    static LoopbackCanTest* getInstance();  // Método de acesso ao singleton

    LoopbackCanTest(const LoopbackCanTest&) = delete;
    LoopbackCanTest& operator=(const LoopbackCanTest&) = delete;
};

#endif // LOOPBACKCANTEST_H
