#pragma once

#include <QtWidgets/QMainWindow>
#include <QtSql>
#include <QVariant>

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
    bool GetIsInEditMode();
    int GetSelectedId();
    int GetMinorSelectedId();
    QVariant GetPreviousCellValue();

    QStringList GetEndMajorNodes();
    QStringList GetEndMinorNodes();

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
    void SetIsInEditMode(bool isInEditMode);
    void SetPreviousCellValue(QVariant cellValue);

    void SetTableSettings(QTableView* table);

    void closeEvent(QCloseEvent* event) override;

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
    void switchButtons();
    void switchMajorTableToEditMode();
    void switchMinorTableToEditMode();
    void switchMinorSubtableToEditMode();
    void representMinorTable();
    void representTable();
    void deleteMajorTableRow();
    void deleteMinorTableRow();
    void deleteMinorSubtableRow();
    void updateMajorTableRow();
    void updateMinorTableRow();
    void updateMinorSubtableRow();

private:
    Ui::FFSDatabaseInterfaceClass ui;

    int selectedId = 0;
    int minorSelectedId = 0;
    QString actualTable = "measuring system";
    QString actualSubtable = "measurements";
    QString actualMinorSubtable = "";
    QVariant previousCellValue;

    bool firstLoad = true;
    bool minorFirstLoad = true;
    bool isRowSelected = false;
    bool isSubRowSelected = false;
    bool isSubtableChanged = false;
    bool isMinorSubtableChanged = false;
    bool isInEditMode = false;

    const QStringList endMinorNodes = {
        "measurement_parameters",
        "equipment_parameters",
        "measuring_systems",
        "characteristics" };

    const QStringList endMajorNodes = {
        "characteristic" };

    const QStringList measurementSelectorItems = {
        "Measurement parameters",
        "Characteristics" };

    const QStringList sampleSelectorItems = {
        "Measurements" };

    const QStringList equipmentSelectorItems = {
        "Equipment parameters",
        "Measuring systems" };

    const QStringList characteristicTypeSelectorItems = {
        "Characteristics" };
};
