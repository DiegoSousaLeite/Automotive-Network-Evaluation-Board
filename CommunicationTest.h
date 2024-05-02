// CommunicationTest.h
#ifndef COMMUNICATIONTEST_H
#define COMMUNICATIONTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class CommunicationTest : public GenericTest {
private:
    static CommunicationTest* instance; // Declarar aqui, mas não inicializar

    CommunicationTest(); // Definir o construtor como privado

public:
    static CommunicationTest* getInstance(); // Declaração do método getInstance

    virtual ~CommunicationTest(); // Destruidor para limpeza

    CommunicationTest(const CommunicationTest&) = delete;
    CommunicationTest& operator=(const CommunicationTest&) = delete;
};

#endif // COMMUNICATIONTEST_H
