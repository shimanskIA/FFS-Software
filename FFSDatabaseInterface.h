#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FFSDatabaseInterface.h"

class FFSDatabaseInterface : public QMainWindow
{
    Q_OBJECT

public:
    FFSDatabaseInterface(QWidget *parent = Q_NULLPTR);

private slots:
    void infoButtonClick();
    void chooseMeasurementTable();
    void chooseMeasuringSystemTable();
    void chooseSampleTable();
    void chooseEquipmentTable();
    void openFileDialog();

private:
    Ui::FFSDatabaseInterfaceClass ui;
};
