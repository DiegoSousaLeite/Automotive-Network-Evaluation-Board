#ifndef LINNETWORKTEST_H
#define LINNETWORKTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class LinNetworkTest : public GenericTest {
private:
    static LinNetworkTest* instance;  // Declaração da instância singleton

    LinNetworkTest();  // Construtor privado

public:
    ~LinNetworkTest();  // Destruidor

    static LinNetworkTest* getInstance();  // Método de acesso ao singleton

    LinNetworkTest(const LinNetworkTest&) = delete;
    LinNetworkTest& operator=(const LinNetworkTest&) = delete;
};

#endif // LINNETWORKTEST_H
