#ifndef REPORTCONTROLLERINTERFACE_H
#define REPORTCONTROLLERINTERFACE_H

class ReportControllerInterface {
public:
    virtual ~ReportControllerInterface() {}

    // Declaração de método virtual puro que precisa ser implementado pelas classes derivadas
    virtual void showCommTestReport() = 0;
};

#endif // REPORTCONTROLLERINTERFACE_H
