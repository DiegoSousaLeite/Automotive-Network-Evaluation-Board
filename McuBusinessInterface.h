#ifndef MCUBUSINESSINTERFACE_H
#define MCUBUSINESSINTERFACE_H

#include <QString>

class McuBusinessInterface {
public:
    virtual ~McuBusinessInterface() {}

//    virtual bool loadProgrammer(int programmerId) = 0;
//    virtual int getSerialProgrammerMode() = 0;
    virtual void addCmdTestMessage(int testId, int boardId, const QString& testMessage, bool header) = 0;
//    virtual int uploadFirmware(int programmerId) = 0;
//    virtual void setSerialProgrammerMode(int progMode) = 0;
//    virtual void executeFirmwareUpload(int programmer_id) = 0;

    enum SerialMode {
        SM_SEL_SL_STATE = 0,
        SM_SEL_UD_STATE = 1,
        SM_SEL_SU_STATE = 2,
        SM_SEL_SD_STATE = 3,
        SM_SEL_SV_STATE = 4
    };
};

#endif // MCUBUSINESSINTERFACE_H
