#ifndef CAN2NETWORKTEST_H
#define CAN2NETWORKTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class CAN2NetworkTest : public GenericTest {
private:
    static CAN2NetworkTest* instance;  // Declaração da instância singleton

    CAN2NetworkTest();  // Construtor privado

public:
    static CAN2NetworkTest* getInstance();  // Método de acesso ao singleton

    virtual ~CAN2NetworkTest();  // Destruidor

    // Impedir cópia e atribuição
    CAN2NetworkTest(const CAN2NetworkTest&) = delete;
    CAN2NetworkTest& operator=(const CAN2NetworkTest&) = delete;
};

#endif // CAN2NETWORKTEST_H
