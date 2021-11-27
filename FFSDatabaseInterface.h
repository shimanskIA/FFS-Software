#pragma once

#include <QtWidgets/QMainWindow>
#include <QtSql>
#include <QVariant>
#include <QMap>

#include "ui_FFSDatabaseInterface.h"
#include "BaseAddForm.h"
#include "CharacteristicPreviewForm.h"

class FFSDatabaseInterface : public QMainWindow
{
    Q_OBJECT

public:
    FFSDatabaseInterface(QWidget *parent = Q_NULLPTR);
    ~FFSDatabaseInterface();

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
    bool GetAddTryMajorTable();
    bool GetAddTryMinorTable();
    bool GetAddTryMinorSubtable();
    int GetSelectedId();
    int GetMinorSelectedId();
    QVariant GetPreviousCellValue();
    QMap<QString, int> &GetForeignKeys();
    QMap<int, CharacteristicPreviewForm*> GetOpenedCharacteristicPreviewWindows();

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
    void SetAddTryMajorTable(bool addTryMajorTable);
    void SetAddTryMinorTable(bool addTryMinorTable);
    void SetAddTryMinorSubtable(bool addTryMinorSubtable);
    void SetSelectedId(int selectedId);
    void SetMinorSelectedId(int minorSelectedId);
    void SetIsInEditMode(bool isInEditMode);
    void SetPreviousCellValue(QVariant cellValue);

    void SetUpAddView(BaseAddForm* addView);

    void SetTableSettings(QTableView* table);

    void AddOpenedCharacteristicPreviewWindow(int, CharacteristicPreviewForm* characteristicPreview);

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
    void showAddRowMajorTableView();
    void showAddRowMinorTableView();
    void showAddRowMinorSubtableView();
    void showWindow();
    void makeWindowVisible();
    void showMajorCharacteristicPreview();
    void showMinorCharacteristicPreview();
    void showMinorCharacteristicSubPreview();
    void closePreviewWindow(int windowId);
    void sortMajorTableRows(int selectedColumn);
    void sortMinorTableRows(int selectedColumn);
    void sortMinorSubtableRows(int selectedColumn);
    void showMajorFilteredRows(QString keyword);
    void showFilteredRows(QString keyword);
    void showMinorFilteredRows(QString keyword);
    void setUpMajorAdvancedSearch(int checkboxState);
    void setUpAdvancedSearch(int checkboxState);
    void setUpMinorAdvancedSearch(int checkboxState);
    void showMajorAdvancedFilteredRows();
    void showAdvancedFilteredRows();
    void showMinorAdvancedFilteredRows();

private:
    Ui::FFSDatabaseInterfaceClass ui;
    BaseAddForm* addView = nullptr;

    int selectedId = 0;
    int minorSelectedId = 0;
    QString actualTable = "";
    QString actualSubtable = "";
    QString actualMinorSubtable = "";
    QVariant previousCellValue;

    QMap<QString, int> foreignKeys;
    QMap<int, CharacteristicPreviewForm*> openedCharacteristicPreviewWindows;

    bool firstLoad = true;
    bool minorFirstLoad = true;
    bool isRowSelected = false;
    bool isSubRowSelected = false;
    bool isSubtableChanged = false;
    bool isMinorSubtableChanged = false;
    bool isInEditMode = false;
    bool addTryMajorTable = false;
    bool addTryMinorTable = false;
    bool addTryMinorSubtable = false;
    bool isMajorAdvancedSearchEnabled = false;
    bool isAdvancedSearchEnabled = false;
    bool isMinorAdvancedSearchEnabled = false;

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
