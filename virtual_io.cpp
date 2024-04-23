#include "virtual_io.h"
#include "ui_virtual_io.h"

Virtual_IO::Virtual_IO(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Virtual_IO)
{
    ui->setupUi(this);
}

Virtual_IO::~Virtual_IO()
{
    delete ui;
}
