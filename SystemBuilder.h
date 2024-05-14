#ifndef SYSTEMBUILDER_H
#define SYSTEMBUILDER_H

#include "SystemBuilder.h"
#include "EcuBusinessController.h"
#include "McuBusinessController.h"
#include "EcuFrameController.h"
#include "McuFrameController.h"
#include "PersistenceController.h"
#include "JigaTestInterface.h"

class SystemBuilder : public SystemBuilder{
public:

    void createSystem(){
        sDefinition = new SystemDefinition;

        //1 - Creating all controller
        ecuFmController = new EcuFrameController();
        mcuFmController = new McuFrameController();
        bsController    = new EcuBusinessController();
        fwController    = new McuBusinessController();
        rpController    = new RepBusinessController();

        psController = PersistenceController::getInstance();
        psController->setReportProperty(sDefinition->getReportProperty(),sDefinition->getReportProperty());

        //2 - Creating all view

        //3 - Setting business controller on frame controller
        ecuFmController->setEcuBusinessController(bsController);
        //3 - Setting business controller on frame controller
        mcuFmController->setMcuBusinessController(fwController);

        //3 - Setting business controller on frame controller
        ecuFmController->setReportController(rpController);

        //3-Set the PersistenceController
        bsController->setPersistenceController(psController);

        //3-Set the PersistenceController
        bsController->setReportController(rpController);

        //3-Set the PersistenceController
        fwController->setPersistenceController(psController);

        //3-Set the PersistenceController
        rpController->setPersistenceController(psController);


        //Load CANBUS status
        ecuFmController->executeTest(JigaTestConstants::MCU_GET_CANBUS_TEST,JigaTestConstants::MCU1_BOARD_ID);

    }

private:
    EcuFrameController*       ecuFmController;
    McuFrameController*       mcuFmController;
    EcuBusinessController*       bsController;
    McuBusinessController*       fwController;
    RepBusinessController*       rpController;

    PersistenceController*       psController;
    SystemDefinition*             sDefinition;

};

#endif // SYSTEMBUILDER_H
