#include "FFSDatabaseInterface.h"
#include "AboutForm.h"
#include "ui_AboutForm.h"
#include "FFSDatabaseInterfaceFormController.h"
#include "FFSTableModel.h"
#include "MeasuringSystemAddForm.h"
#include "MeasuringSystemInputForm.h"

#include <QFileDialog>
#include <QCloseEvent>
#include <QTableWidget>
#include <QAbstractItemModel>

FFSDatabaseInterface::FFSDatabaseInterface(QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    FFSTableModel* majorTableModel = new FFSTableModel(0, 0);
    FFSTableModel* minorTableModel = new FFSTableModel(0, 0);
    FFSTableModel* minorSubtableModel = new FFSTableModel(0, 0);
    ui.majorTableView->setModel(majorTableModel);
    ui.minorTableView->setModel(minorTableModel);
    ui.minorSubtableView->setModel(minorSubtableModel);
    ui.majorButtonsBox->setStyleSheet("QGroupBox { border:none; }");
    ui.minorButtonsBox->setStyleSheet("QGroupBox { border:none; }");
    ui.minorButtonsSubbox->setStyleSheet("QGroupBox { border:none; }");
    foreignKeys.insert("measuring system", 0);
    foreignKeys.insert("equipment", 0);
    foreignKeys.insert("sample", 0);
    foreignKeys.insert("characteristic type", 0);
    foreignKeys.insert("measurement", 0);
    connect(ui.actionInfo, SIGNAL(triggered()), this, SLOT(infoButtonClick()));
    connect(ui.actionMeasuringSystem, SIGNAL(triggered()), this, SLOT(chooseMeasuringSystemTable()));
    connect(ui.actionSample, SIGNAL(triggered()), this, SLOT(chooseSampleTable()));
    connect(ui.actionEquipment, SIGNAL(triggered()), this, SLOT(chooseEquipmentTable()));
    connect(ui.actionMeasurement, SIGNAL(triggered()), this, SLOT(chooseMeasurementTable()));
    connect(ui.actionCharacteristicType, SIGNAL(triggered()), this, SLOT(chooseCharacteristicTypeTable()));
    connect(ui.actionCharacteristic, SIGNAL(triggered()), this, SLOT(chooseCharacteristicTable()));
    connect(ui.actionImport, SIGNAL(triggered()), this, SLOT(openFileDialog()));
    connect(ui.majorTableView, SIGNAL(clicked(QModelIndex)), this, SLOT(loadDataToSubtable()));
    connect(ui.majorTableView->model(), &QAbstractItemModel::dataChanged, this, &FFSDatabaseInterface::updateMajorTableRow);
    connect(ui.majorTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(switchMajorTableToEditMode()));
    connect(ui.minorTableView, SIGNAL(clicked(QModelIndex)), this, SLOT(loadDataToMinorSubtable()));
    connect(ui.minorTableView->model(), &QAbstractItemModel::dataChanged, this, &FFSDatabaseInterface::updateMinorTableRow);
    connect(ui.minorTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(switchMinorTableToEditMode()));
    connect(ui.minorSubtableView, SIGNAL(clicked(QModelIndex)), this, SLOT(switchButtons()));
    connect(ui.minorSubtableView->model(), &QAbstractItemModel::dataChanged, this, &FFSDatabaseInterface::updateMinorSubtableRow);
    connect(ui.minorSubtableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(switchMinorSubtableToEditMode()));
    connect(ui.tableSelector, SIGNAL(activated(QString)), this, SLOT(representTable()));
    connect(ui.minorTableSelector, SIGNAL(activated(QString)), this, SLOT(representMinorTable()));
    connect(ui.majorDeleteButton, SIGNAL(clicked()), this, SLOT(deleteMajorTableRow()));
    connect(ui.minorDeleteButton, SIGNAL(clicked()), this, SLOT(deleteMinorTableRow()));
    connect(ui.minorDeleteSubbutton, SIGNAL(clicked()), this, SLOT(deleteMinorSubtableRow()));
    connect(ui.majorAddButton, SIGNAL(clicked()), this, SLOT(showAddRowMajorTableView()));
    connect(ui.minorAddButton, SIGNAL(clicked()), this, SLOT(showAddRowMinorTableView()));
    connect(ui.minorAddSubbutton, SIGNAL(clicked()), this, SLOT(showAddRowMinorSubtableView()));
    connect(ui.majorPreviewButton, SIGNAL(clicked()), this, SLOT(showMajorCharacteristicPreview()));
    connect(ui.minorPreviewButton, SIGNAL(clicked()), this, SLOT(showMinorCharacteristicPreview()));
    connect(ui.minorPreviewSubbutton, SIGNAL(clicked()), this, SLOT(showMinorCharacteristicSubPreview()));
    connect(ui.majorSearchInput, SIGNAL(textChanged(QString)), this, SLOT(showMajorFilteredRows(QString)));
    connect(ui.searchInput, SIGNAL(textChanged(QString)), this, SLOT(showFilteredRows(QString)));
    connect(ui.minorSearchInput, SIGNAL(textChanged(QString)), this, SLOT(showMinorFilteredRows(QString)));
    connect(ui.majorAdvancedSearchCheckbox, SIGNAL(stateChanged(int)), this, SLOT(setUpMajorAdvancedSearch(int)));
    connect(ui.advancedSearchCheckbox, SIGNAL(stateChanged(int)), this, SLOT(setUpAdvancedSearch(int)));
    connect(ui.minorAdvancedSearchCheckbox, SIGNAL(stateChanged(int)), this, SLOT(setUpMinorAdvancedSearch(int)));
    connect(ui.majorTableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortMajorTableRows(int)));
    connect(ui.minorTableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortMinorTableRows(int)));
    connect(ui.minorSubtableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortMinorSubtableRows(int)));
    FFSDatabaseInterfaceFormController::ManageShowMajorTableRequest("measurement", "measurement_parameters", measurementSelectorItems, this);
    SetTableSettings(ui.majorTableView);
}

FFSDatabaseInterface::~FFSDatabaseInterface()
{
    qDeleteAll(openedCharacteristicPreviewWindows);
    openedCharacteristicPreviewWindows.clear();
}

void FFSDatabaseInterface::infoButtonClick()
{
    AboutForm::GetAboutFormInstance().showNormal();
}

void FFSDatabaseInterface::chooseMeasuringSystemTable()
{
    FFSDatabaseInterfaceFormController::ManageShowMeasuringSystemTableRequest(this);
}

void FFSDatabaseInterface::chooseMeasurementTable()
{
    FFSDatabaseInterfaceFormController::ManageShowMajorTableRequest("measurement", "measurement_parameters", measurementSelectorItems, this);
}

void FFSDatabaseInterface::chooseSampleTable()
{
    FFSDatabaseInterfaceFormController::ManageShowMajorTableRequest("sample", "measurements", sampleSelectorItems, this);
}

void FFSDatabaseInterface::chooseEquipmentTable()
{
    FFSDatabaseInterfaceFormController::ManageShowMajorTableRequest("equipment", "equipment_parameters", equipmentSelectorItems, this);
}

void FFSDatabaseInterface::chooseCharacteristicTypeTable()
{
    FFSDatabaseInterfaceFormController::ManageShowMajorTableRequest("characteristic type", "characteristics", characteristicTypeSelectorItems, this);
}

void FFSDatabaseInterface::chooseCharacteristicTable()
{
    FFSDatabaseInterfaceFormController::ManageShowCharacteristicsTableRequest(this);
}

void FFSDatabaseInterface::openFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName();
    if (filePath != nullptr)
    {
        FFSDatabaseInterfaceFormController::ManageFileImportRequest(filePath);
        FFSDatabaseInterfaceFormController::ManageRefreshMajorTableRequest(this);
    }
}

void FFSDatabaseInterface::loadDataToSubtable()
{
    FFSDatabaseInterfaceFormController::ManageLoadDataToSubtableRequest(this);
}

void FFSDatabaseInterface::loadDataToMinorSubtable()
{
    FFSDatabaseInterfaceFormController::ManageLoadDataToMinorSubtableRequest(this);
}

void FFSDatabaseInterface::switchButtons()
{
    FFSDatabaseInterfaceFormController::ManageSwitchButtonsRequest(this);
}

void FFSDatabaseInterface::representTable()
{
    FFSDatabaseInterfaceFormController::ManageRepresentSubtableRequest(this);
}

void FFSDatabaseInterface::representMinorTable()
{
    FFSDatabaseInterfaceFormController::ManageRepresentMinorSubtableRequest(this);
}

void FFSDatabaseInterface::deleteMajorTableRow()
{
    FFSDatabaseInterfaceFormController::ManageDeleteRowRequest(ui.majorTableView, actualTable + "s");
    FFSDatabaseInterfaceFormController::ManageRefreshMajorTableRequest(this);
}

void FFSDatabaseInterface::deleteMinorTableRow()
{

    FFSDatabaseInterfaceFormController::ManageDeleteRowRequest(ui.minorTableView, actualSubtable);
    isSubtableChanged = true;
    FFSDatabaseInterfaceFormController::ManageLoadDataToSubtableRequest(this);
}

void FFSDatabaseInterface::deleteMinorSubtableRow()
{
    FFSDatabaseInterfaceFormController::ManageDeleteRowRequest(ui.minorSubtableView, actualMinorSubtable);
    isMinorSubtableChanged = true;
    FFSDatabaseInterfaceFormController::ManageLoadDataToMinorSubtableRequest(this);
}

void FFSDatabaseInterface::switchMajorTableToEditMode()
{
    FFSDatabaseInterfaceFormController::ManageSwitchToEditModeRequest(ui.majorTableView, this);
}

void FFSDatabaseInterface::switchMinorTableToEditMode()
{
    FFSDatabaseInterfaceFormController::ManageSwitchToEditModeRequest(ui.minorTableView, this);
}

void FFSDatabaseInterface::switchMinorSubtableToEditMode()
{
    FFSDatabaseInterfaceFormController::ManageSwitchToEditModeRequest(ui.minorSubtableView, this);
}

void FFSDatabaseInterface::updateMajorTableRow()
{
    FFSDatabaseInterfaceFormController::ManageUpdateTableRequest(actualTable + "s", ui.majorTableView, this);
}

void FFSDatabaseInterface::updateMinorTableRow()
{
    FFSDatabaseInterfaceFormController::ManageUpdateTableRequest(actualSubtable, ui.minorTableView, this);
}

void FFSDatabaseInterface::updateMinorSubtableRow()
{
    FFSDatabaseInterfaceFormController::ManageUpdateTableRequest(actualMinorSubtable, ui.minorSubtableView, this);
}

void FFSDatabaseInterface::showAddRowMajorTableView()
{
    addTryMajorTable = true;
    FFSDatabaseInterfaceFormController::ManageShowAddViewRequest(actualTable + "s", this);
}

void FFSDatabaseInterface::showAddRowMinorTableView()
{
    addTryMinorTable = true;
    FFSDatabaseInterfaceFormController::ManageShowMinorAddViewRequest(actualSubtable, this);
}

void FFSDatabaseInterface::showAddRowMinorSubtableView()
{
    addTryMinorSubtable = true;
    FFSDatabaseInterfaceFormController::ManageShowMinorAddViewSubRequest(actualMinorSubtable, this);
}

void FFSDatabaseInterface::showWindow()
{
    FFSDatabaseInterfaceFormController::ManageRefreshViewRequest(this, addView->GetIsRowAdded());
    addView->close();
    this->show();
}

void FFSDatabaseInterface::makeWindowVisible()
{
    this->show();
}

void FFSDatabaseInterface::showMajorCharacteristicPreview()
{
    FFSDatabaseInterfaceFormController::ManageShowCharacteristicPreviewRequest(ui.majorTableView, this);
}

void FFSDatabaseInterface::showMinorCharacteristicPreview()
{
    FFSDatabaseInterfaceFormController::ManageShowCharacteristicPreviewRequest(ui.minorTableView, this);
}

void FFSDatabaseInterface::showMinorCharacteristicSubPreview()
{
    FFSDatabaseInterfaceFormController::ManageShowCharacteristicPreviewRequest(ui.minorSubtableView, this);
}

void FFSDatabaseInterface::SetUpAddView(BaseAddForm* addView)
{
    this->addView = addView;
    connect(addView, &BaseAddForm::windowClosed, this, &FFSDatabaseInterface::showWindow);
}

void FFSDatabaseInterface::AddOpenedCharacteristicPreviewWindow(int windowId, CharacteristicPreviewForm* characteristicPreview)
{
    this->openedCharacteristicPreviewWindows.insert(windowId, characteristicPreview);
    connect(characteristicPreview, &CharacteristicPreviewForm::previewWindowClosed, this, &FFSDatabaseInterface::closePreviewWindow);
}

void FFSDatabaseInterface::closePreviewWindow(int windowId)
{
    this->openedCharacteristicPreviewWindows.remove(windowId);
}

void FFSDatabaseInterface::sortMajorTableRows(int selectedColumn)
{
    FFSDatabaseInterfaceFormController::ManageSortRowsRequest(ui.majorTableView, selectedColumn);
}

void FFSDatabaseInterface::sortMinorTableRows(int selectedColumn)
{
    FFSDatabaseInterfaceFormController::ManageSortRowsRequest(ui.minorTableView, selectedColumn);
}

void FFSDatabaseInterface::sortMinorSubtableRows(int selectedColumn)
{
    FFSDatabaseInterfaceFormController::ManageSortRowsRequest(ui.minorSubtableView, selectedColumn);
}

void FFSDatabaseInterface::showMajorFilteredRows(QString keyword)
{
    FFSDatabaseInterfaceFormController::ManageShowFilteredRowsRequest(ui.majorTableView, keyword, (FFSTableModel*)ui.minorTableView->model());
}

void FFSDatabaseInterface::showFilteredRows(QString keyword)
{
    FFSDatabaseInterfaceFormController::ManageShowFilteredRowsRequest(ui.minorTableView, keyword, (FFSTableModel*)ui.minorSubtableView->model());
}

void FFSDatabaseInterface::showMinorFilteredRows(QString keyword)
{
    FFSDatabaseInterfaceFormController::ManageShowFilteredRowsRequest(ui.minorSubtableView, keyword);
}

void FFSDatabaseInterface::setUpMajorAdvancedSearch(int checkboxState)
{   
    if (checkboxState == Qt::Checked)
    {
        ui.majorSearchInput->setText("");
        ui.majorSearchInput->disconnect();
        connect(ui.majorSearchInput, SIGNAL(editingFinished()), this, SLOT(showMajorAdvancedFilteredRows()));
    }
    else
    {
        ui.majorSearchInput->disconnect();
        connect(ui.majorSearchInput, SIGNAL(textChanged(QString)), this, SLOT(showMajorFilteredRows(QString)));
        ui.majorSearchInput->setText("");
    }
}

void FFSDatabaseInterface::setUpAdvancedSearch(int checkboxState)
{
    if (checkboxState == Qt::Checked)
    {
        ui.searchInput->setText("");
        ui.searchInput->disconnect();
        connect(ui.searchInput, SIGNAL(editingFinished()), this, SLOT(showAdvancedFilteredRows()));
    }
    else
    {
        ui.searchInput->disconnect();
        connect(ui.searchInput, SIGNAL(textChanged(QString)), this, SLOT(showFilteredRows(QString)));
        ui.searchInput->setText("");
    }
}

void FFSDatabaseInterface::setUpMinorAdvancedSearch(int checkboxState)
{
    if (checkboxState == Qt::Checked)
    {
        ui.minorSearchInput->setText("");
        ui.minorSearchInput->disconnect();
        connect(ui.minorSearchInput, SIGNAL(editingFinished()), this, SLOT(showMinorAdvancedFilteredRows()));
    }
    else
    {
        ui.minorSearchInput->disconnect();
        connect(ui.minorSearchInput, SIGNAL(textChanged(QString)), this, SLOT(showMinorFilteredRows(QString)));
        ui.minorSearchInput->setText("");
    }
}

void FFSDatabaseInterface::showMajorAdvancedFilteredRows()
{
    FFSDatabaseInterfaceFormController::ManageShowAdvancedFilteredRowsRequest(ui.majorTableView, ui.majorSearchInput->text(), (FFSTableModel*)ui.minorTableView->model());
}

void FFSDatabaseInterface::showAdvancedFilteredRows()
{
    FFSDatabaseInterfaceFormController::ManageShowAdvancedFilteredRowsRequest(ui.minorTableView, ui.searchInput->text(), (FFSTableModel*)ui.minorSubtableView);
}

void FFSDatabaseInterface::showMinorAdvancedFilteredRows()
{
    FFSDatabaseInterfaceFormController::ManageShowAdvancedFilteredRowsRequest(ui.minorSubtableView, ui.minorSearchInput->text());
}

void FFSDatabaseInterface::SetTableSettings(QTableView* table)
{
    table->setColumnHidden(0, true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::DoubleClicked);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setDefaultSectionSize(20);
    table->verticalHeader()->sectionResizeMode(QHeaderView::Fixed);
    table->setStyleSheet(
        "QHeaderView::section { background-color: rgb(217, 217, 217)}"
        "QTableView {selection-background-color: steelblue}");
}

void FFSDatabaseInterface::closeEvent(QCloseEvent* event)
{
    FFSDatabaseInterfaceFormController::ManageRemoveUnusedIdsRequest();
    event->accept();
}

Ui::FFSDatabaseInterfaceClass FFSDatabaseInterface::GetUI()
{
    return this->ui;
}

QString FFSDatabaseInterface::GetActualTable()
{
    return this->actualTable;
}

QString FFSDatabaseInterface::GetActualSubtable()
{
    return this->actualSubtable;
}

QString FFSDatabaseInterface::GetActualMinorSubtable()
{
    return this->actualMinorSubtable;
}

bool FFSDatabaseInterface::GetIsRowSelected()
{
    return this->isRowSelected;
}

bool FFSDatabaseInterface::GetIsSubRowSelected()
{
    return this->isSubRowSelected;
}

bool FFSDatabaseInterface::GetFirstLoad()
{
    return this->firstLoad;
}

bool FFSDatabaseInterface::GetMinorFirstLoad()
{
    return this->minorFirstLoad;
}

bool FFSDatabaseInterface::GetIsSubtableChanged()
{
    return this->isSubtableChanged;
}

bool FFSDatabaseInterface::GetIsMinorSubtableChanged()
{
    return this->isMinorSubtableChanged;
}

bool FFSDatabaseInterface::GetIsInEditMode()
{
    return this->isInEditMode;
}

bool FFSDatabaseInterface::GetAddTryMajorTable()
{
    return this->addTryMajorTable;
}

bool FFSDatabaseInterface::GetAddTryMinorTable()
{
    return this->addTryMinorTable;
}

bool FFSDatabaseInterface::GetAddTryMinorSubtable()
{
    return this->addTryMinorSubtable;
}

int FFSDatabaseInterface::GetSelectedId()
{
    return this->selectedId;
}

int FFSDatabaseInterface::GetMinorSelectedId()
{
    return this->minorSelectedId;
}

QVariant FFSDatabaseInterface::GetPreviousCellValue()
{
    return this->previousCellValue;
}

QMap<QString, int>& FFSDatabaseInterface::GetForeignKeys()
{
    return this->foreignKeys;
}

QMap<int, CharacteristicPreviewForm*> FFSDatabaseInterface::GetOpenedCharacteristicPreviewWindows()
{
    return this->openedCharacteristicPreviewWindows;
}

QStringList FFSDatabaseInterface::GetEndMajorNodes()
{
    return this->endMajorNodes;
}

QStringList FFSDatabaseInterface::GetEndMinorNodes()
{
    return this->endMinorNodes;
}

void FFSDatabaseInterface::SetActualTable(QString actualTable)
{
    this->actualTable = actualTable;
}

void FFSDatabaseInterface::SetActualSubtable(QString actualSubtable)
{
    this->actualSubtable = actualSubtable;
}

void FFSDatabaseInterface::SetActualMinorSubtable(QString actualMinorSubtable)
{
    this->actualMinorSubtable = actualMinorSubtable;
}

void FFSDatabaseInterface::SetIsRowSelected(bool isRowSelected)
{
    this->isRowSelected = isRowSelected;
}

void FFSDatabaseInterface::SetIsSubRowSelected(bool isSubRowSelected)
{
    this->isSubRowSelected = isSubRowSelected;
}

void FFSDatabaseInterface::SetIsSubtableChanged(bool isSubtableChanged)
{
    this->isSubtableChanged = isSubtableChanged;
}

void FFSDatabaseInterface::SetIsMinorSubtableChanged(bool isMinorSubtableChanged)
{
    this->isMinorSubtableChanged = isMinorSubtableChanged;
}

void FFSDatabaseInterface::SetFirstLoad(bool firstLoad)
{
    this->firstLoad = firstLoad;
}

void FFSDatabaseInterface::SetMinorFirstLoad(bool minorFirstLoad)
{
    this->minorFirstLoad = minorFirstLoad;
}

void FFSDatabaseInterface::SetIsInEditMode(bool isInEditMode)
{
    this->isInEditMode = isInEditMode;
}

void FFSDatabaseInterface::SetAddTryMajorTable(bool addTryMajorTable)
{
    this->addTryMajorTable = addTryMajorTable;
}

void FFSDatabaseInterface::SetAddTryMinorTable(bool addTryMinorTable)
{
    this->addTryMinorTable = addTryMinorTable;
}

void FFSDatabaseInterface::SetAddTryMinorSubtable(bool addTryMinorSubtable)
{
    this->addTryMinorSubtable = addTryMinorSubtable;
}

void FFSDatabaseInterface::SetPreviousCellValue(QVariant cellValue)
{
    this->previousCellValue = cellValue;
}

void FFSDatabaseInterface::SetSelectedId(int selectedId)
{
    this->selectedId = selectedId;
}

void FFSDatabaseInterface::SetMinorSelectedId(int minorSelectedId)
{
    this->minorSelectedId = minorSelectedId;
}