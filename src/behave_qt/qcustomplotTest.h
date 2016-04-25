#ifndef QCUSTOMPLOTTEST_HEADER
#define QCUSTOMPLOTTEST_HEADER

#include <QtWidgets/QMainWindow>
#include "ui_qcustomplot_test.h"
#include "behaveVector.h"

class QcustomplotTest : public QMainWindow
{
    Q_OBJECT

public:
    QcustomplotTest(QWidget* parent = 0);
    ~QcustomplotTest();

public slots:
  

private:
    //void establishConnections();
  
    Ui::qcustomplot_testClass ui;
    BehaveVector behaveVector;
};

#endif // QCUSTOMPLOTTEST_HEADER
