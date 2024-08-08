#ifndef CANLOOPBACKTEST_H
#define CANLOOPBACKTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class CANLoopbackTest : public GenericTest {
private:
    static CANLoopbackTest* instance;  // Declaração da instância singleton

    CANLoopbackTest();  // Construtor privado

public:
    virtual ~CANLoopbackTest();  // Destruidor

    static CANLoopbackTest* getInstance();  // Método de acesso ao singleton

    CANLoopbackTest(const CANLoopbackTest&) = delete;
    CANLoopbackTest& operator=(const CANLoopbackTest&) = delete;
};

#endif // CANLOOPBACKTEST_H
