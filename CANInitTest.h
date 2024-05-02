#ifndef CANINITTEST_H
#define CANINITTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class CANInitTest : public GenericTest {
private:
    static CANInitTest* instance;

    CANInitTest();  // Declaração do construtor privado

public:
    static CANInitTest* getInstance();  // Método de acesso ao singleton

    virtual ~CANInitTest();  // Declaração do destruidor

    // Impedir cópia e atribuição
    CANInitTest(const CANInitTest&) = delete;
    CANInitTest& operator=(const CANInitTest&) = delete;
};

#endif // CANINITTEST_H
