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
    void chooseMeasuringSystemTable();
    void chooseCharacteristicTypeTable();
    void chooseCharacteristicTable();
    void openFileDialog();
    void loadDataToSubtable();
    void loadDataToMinorSubtable();
    void representMinorTable();
    void representTable();

private:
    Ui::FFSDatabaseInterfaceClass ui;

    int selectedId = 0;
    int minorSelectedId = 0;
    QString actualTable = "measuring system";
    QString actualSubtable = "measurements";
    QString actualMinorSubtable = "";

    bool firstLoad = true;
    bool minorFirstLoad = true;
    bool isRowSelected = false;
    bool isSubRowSelected = false;
    bool isSubtableChanged = false;
    bool isMinorSubtableChanged = false;

    void SetTableSettings(QTableView* table);
};
