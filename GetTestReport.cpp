#include "GetTestReport.h"
#include <QDebug>

GetTestReport::GetTestReport(QObject *parent) : QObject(parent) {}

void GetTestReport::getTestResult(int test_id, int board_id) {
    qDebug() << "GetTestReport: listener timeout event!";
    qDebug() << "GetTestReport: board_id =" << board_id;
    qDebug() << "GetTestReport: test_id  =" << test_id;
}
