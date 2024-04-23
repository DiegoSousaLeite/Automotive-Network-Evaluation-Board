#ifndef VIRTUAL_IO_H
#define VIRTUAL_IO_H

#include <QWidget>
#include "ui_virtual_io.h"

namespace Ui {
class Virtual_IO;
}

class Virtual_IO : public QWidget
{
    Q_OBJECT

public:
    explicit Virtual_IO(QWidget *parent = nullptr);
    ~Virtual_IO();

private:
    Ui::Virtual_IO *ui;
};

#endif // VIRTUAL_IO_H
