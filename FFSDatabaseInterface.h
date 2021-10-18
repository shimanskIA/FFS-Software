#pragma once

#include <QtWidgets/QMainWindow>
#include <QtSql>

#include "ui_FFSDatabaseInterface.h"

class FFSDatabaseInterface : public QMainWindow
{
    Q_OBJECT

public:
    FFSDatabaseInterface(QWidget *parent = Q_NULLPTR);

private slots:
    void infoButtonClick();
    void chooseMeasurementTable();
    void chooseSampleTable();
    void chooseEquipmentTable();
    void openFileDialog();

    void SetTableSettings(QTableView* table);

private:
    Ui::FFSDatabaseInterfaceClass ui;
};
