#ifndef CAN1NETWORKTEST_H
#define CAN1NETWORKTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class CAN1NetworkTest : public GenericTest {
private:
    static CAN1NetworkTest* instance;  // Declaração da instância singleton

    CAN1NetworkTest();  // Construtor privado

public:
    static CAN1NetworkTest* getInstance();  // Método de acesso ao singleton

    virtual ~CAN1NetworkTest();  // Destruidor

    // Impedir cópia e atribuição
    CAN1NetworkTest(const CAN1NetworkTest&) = delete;
    CAN1NetworkTest& operator=(const CAN1NetworkTest&) = delete;
};

#endif // CAN1NETWORKTEST_H
