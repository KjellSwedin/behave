#ifndef BEHAVE_QT_GUI_H
#define BEHAVE_QT_GUI_H

#include "qtIncludesSilencedW4.h"
#include "ui_behave_qt_main_window.h"

#include "behaveRun.h"
#include "behave_qt_main_window_enums.h"
#include "fuelModelSet.h"

class QcustomplotTest;

class BehaveQtMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    BehaveQtMainWindow(QWidget* parent = 0);
    ~BehaveQtMainWindow();

public slots:
    void fuelModelInputChanged(const QString& text);
    void oneHourMoistureInputChanged(const QString& text);
    void tenHourMoistureInputChanged(const QString& text);
    void hundredHourMoistureInputChanged(const QString& text);
    void liveHerbaceousMoistureInputChanged(const QString& text);
    void liveWoodyMoistureInputChanged(const QString& text);
    void windSpeedInputChanged(const QString& text);
    void slopeInputChanged(const QString& text);
    void calculateClicked();

private:
    void establishConnections();
    void populateTree();

    Ui::behave_qt_main_windowClass ui;
    QcustomplotTest* qcustomplotTest_;
    FuelModelSet fuelModelSet;
    BehaveRun behaveRun;
};
#endif // BEHAVE_QT_GUI_H
