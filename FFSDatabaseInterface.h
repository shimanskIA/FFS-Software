#pragma once

#include <QtWidgets/QMainWindow>
#include <QtSql>

#include "ui_FFSDatabaseInterface.h"

class FFSDatabaseInterface : public QMainWindow
{
    Q_OBJECT

public:
    FFSDatabaseInterface(QWidget *parent = Q_NULLPTR);

    Ui::FFSDatabaseInterfaceClass GetUI();
    QString GetActualTable();
    QString GetActualSubtable();
    QString GetActualMinorSubtable();
    bool GetIsRowSelected();
    bool GetIsSubRowSelected();
    bool GetFirstLoad();
    bool GetMinorFirstLoad();
    bool GetIsSubtableChanged();
    bool GetIsMinorSubtableChanged();
    int GetSelectedId();
    int GetMinorSelectedId();

    void SetActualTable(QString actualTable);
    void SetActualSubtable(QString actualSubtable);
    void SetActualMinorSubtable(QString actualMinorSubtable);
    void SetIsRowSelected(bool isRowSelected);
    void SetIsSubRowSelected(bool isSubRowSelected);
    void SetFirstLoad(bool firstLoad);
    void SetMinorFirstLoad(bool minorFirstLoad);
    void SetIsSubtableChanged(bool isSubtableChanged);
    void SetIsMinorSubtableChanged(bool isMinorSubtableChanged);
    void SetSelectedId(int selectedId);
    void SetMinorSelectedId(int minorSelectedId);

    void SetTableSettings(QTableView* table);

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
};
