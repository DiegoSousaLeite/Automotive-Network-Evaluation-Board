#ifndef REPORTCONTROLLERINTERFACE_H
#define REPORTCONTROLLERINTERFACE_H

class ReportControllerInterface {
public:
    virtual ~ReportControllerInterface() {}

    // Declaração de método virtual puro que precisa ser implementado pelas classes derivadas
    virtual void showCommunicationTestReport() = 0;
    virtual void showDigitalInputTestReport()  = 0;
    virtual void showAnalogInputTestReport()   = 0;
    virtual void showAnalogOutputTestReport()  = 0;
    virtual void showCanInitTestReport()       = 0;
    virtual void showCanLoopbackTestReport()   = 0;
    virtual void showCan1NetworkTestReport()   = 0;
    virtual void showCan2NetworkTestReport()   = 0;
    virtual void showLinNetworkTestReport()    = 0;
};

#endif // REPORTCONTROLLERINTERFACE_H
