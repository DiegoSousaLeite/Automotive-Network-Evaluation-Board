#ifndef FIRMWAREUPLOAD_H
#define FIRMWAREUPLOAD_H

#include "GenericTest.h"

class FirmwareUpload : public GenericTest {
public:
    static FirmwareUpload* getInstance();
    FirmwareUpload();

private:
    static FirmwareUpload* instance;
};

#endif // FIRMWAREUPLOAD_H
