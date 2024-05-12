#ifndef GETTESTREPORT_H
#define GETTESTREPORT_H


#include <QObject>
#include "TimeOutListener.h"

class GetTestReport : public QObject, public TimeOutListener {
    Q_OBJECT

public:
    explicit GetTestReport(QObject *parent = nullptr);
    void getTestResult(int test_id, int board_id) override;
};

#endif // GETTESTREPORT_H
