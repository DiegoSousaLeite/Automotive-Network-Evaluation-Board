#ifndef FIRMWAREUPLOAD_H
#define FIRMWAREUPLOAD_H

#include "generictest.h"

class FirmwareUpload : public GenericTest {
public:
    static FirmwareUpload* getInstance();

protected:
    FirmwareUpload();

private:
    static FirmwareUpload* instance;
};

#endif // FIRMWAREUPLOAD_H
