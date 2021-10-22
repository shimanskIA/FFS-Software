#include "FFSDatabaseInterface.h"
#include "AboutForm.h"
#include "ui_AboutForm.h"
#include "FFSDatabaseInterfaceFormController.h"

#include <QFileDialog>

FFSDatabaseInterface::FFSDatabaseInterface(QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.actionInfo, SIGNAL(triggered()), this, SLOT(infoButtonClick()));
    connect(ui.actionMeasuringSystem, SIGNAL(triggered()), this, SLOT(chooseMeasuringSystemTable()));
    connect(ui.actionSample, SIGNAL(triggered()), this, SLOT(chooseSampleTable()));
    connect(ui.actionEquipment, SIGNAL(triggered()), this, SLOT(chooseEquipmentTable()));
    connect(ui.actionMeasurement, SIGNAL(triggered()), this, SLOT(chooseMeasurementTable()));
    connect(ui.actionCharacteristicType, SIGNAL(triggered()), this, SLOT(chooseCharacteristicTypeTable()));
    connect(ui.actionCharacteristic, SIGNAL(triggered()), this, SLOT(chooseCharacteristicTable()));
    connect(ui.actionImport, SIGNAL(triggered()), this, SLOT(openFileDialog()));
    connect(ui.majorTableView, SIGNAL(clicked(QModelIndex)), this, SLOT(loadDataToSubtable()));
    connect(ui.minorTableView, SIGNAL(clicked(QModelIndex)), this, SLOT(loadDataToMinorSubtable()));
    connect(ui.tableSelector, SIGNAL(activated(QString)), this, SLOT(representTable()));
    connect(ui.minorTableSelector, SIGNAL(activated(QString)), this, SLOT(representMinorTable()));
    FFSDatabaseInterfaceFormController::ManageShowMeasuringSystemTableRequest(ui);
    ui.tableSelector->addItem("Measurements");
    ui.tableSelector->addItem("Equipments");
    ui.tableName->setText((actualTable + "s:").toUpper());
    ui.minorSubtableView->setDisabled(true);
    ui.minorTableSelector->setDisabled(true);
    SetTableSettings(ui.majorTableView);
}

void FFSDatabaseInterface::infoButtonClick()
{
    AboutForm* aboutForm = new AboutForm();
    aboutForm->show();
}

void FFSDatabaseInterface::chooseMeasuringSystemTable()
{
    QString tableName = "measuring system";
    if (actualTable != tableName)
    {
        ui.minorTableView->setModel(nullptr);
        ui.minorSubtableView->setModel(nullptr);
        ui.tableSelector->setDisabled(false);
        ui.minorTableView->setDisabled(false);
        actualSubtable = "measurements";
        ui.tableName->setText((tableName + "s:").toUpper());
        ui.minorTableSelector->clear();
        ui.tableSelector->clear();
        ui.tableSelector->addItem("Measurements");
        ui.tableSelector->addItem("Equipments");
        actualTable = tableName;
        FFSDatabaseInterfaceFormController::ManageShowMeasuringSystemTableRequest(ui);
        isRowSelected = false;
    }
}

void FFSDatabaseInterface::chooseMeasurementTable()
{
    QString tableName = "measurement";
    if (actualTable != tableName)
    {
        ui.minorTableView->setModel(nullptr);
        ui.minorSubtableView->setModel(nullptr);
        ui.tableSelector->setDisabled(false);
        ui.minorTableView->setDisabled(false);
        actualSubtable = "measurement_parameters";
        ui.tableName->setText((tableName + "s:").toUpper());
        ui.minorTableSelector->clear();
        ui.tableSelector->clear();
        ui.tableSelector->addItem("Measurement parameters");
        ui.tableSelector->addItem("Characteristics");
        ui.minorSubtableView->setDisabled(true);
        ui.minorTableSelector->setDisabled(true);
        actualTable = tableName;
        FFSDatabaseInterfaceFormController::ManageShowMeasurementTableRequest(ui);
        isRowSelected = false;
    }
}

void FFSDatabaseInterface::chooseSampleTable()
{
    QString tableName = "sample";
    if (actualTable != tableName)
    {
        ui.minorTableView->setModel(nullptr);
        ui.minorSubtableView->setModel(nullptr);
        ui.tableSelector->setDisabled(false);
        ui.minorTableView->setDisabled(false);
        actualSubtable = "measurements";
        ui.tableName->setText((tableName + "s:").toUpper());
        ui.minorTableSelector->clear();
        ui.tableSelector->clear();
        ui.tableSelector->addItem("Measurements");
        ui.minorSubtableView->setDisabled(true);
        ui.minorTableSelector->setDisabled(true);
        actualTable = tableName;
        FFSDatabaseInterfaceFormController::ManageShowSampleTableRequest(ui);
        isRowSelected = false;
    }
}

void FFSDatabaseInterface::chooseEquipmentTable()
{
    QString tableName = "equipment";
    if (actualTable != tableName)
    {
        ui.minorTableView->setModel(nullptr);
        ui.minorSubtableView->setModel(nullptr);
        ui.tableSelector->setDisabled(false);
        ui.minorTableView->setDisabled(false);
        actualSubtable = "equipment_parameters";
        ui.tableName->setText((tableName + "s:").toUpper());
        ui.minorTableSelector->clear();
        ui.tableSelector->clear();
        ui.tableSelector->addItem("Equipment parameters");
        ui.tableSelector->addItem("Measuring systems");
        ui.minorSubtableView->setDisabled(true);
        ui.minorTableSelector->setDisabled(true);
        actualTable = tableName;
        FFSDatabaseInterfaceFormController::ManageShowEquipmentTableRequest(ui);
        isRowSelected = false;
    }
}

void FFSDatabaseInterface::chooseCharacteristicTypeTable()
{
    QString tableName = "characteristic type";
    if (actualTable != tableName)
    {
        ui.minorTableView->setModel(nullptr);
        ui.minorSubtableView->setModel(nullptr);
        ui.tableSelector->setDisabled(false);
        ui.minorTableView->setDisabled(false);
        actualSubtable = "characteristics";
        ui.tableName->setText((tableName + "s:").toUpper());
        ui.minorTableSelector->clear();
        ui.tableSelector->clear();
        ui.tableSelector->addItem("Characteristics");
        ui.minorSubtableView->setDisabled(true);
        ui.minorTableSelector->setDisabled(true);
        actualTable = tableName;
        FFSDatabaseInterfaceFormController::ManageShowCharacteristicTypesTableRequest(ui);
        isRowSelected = false;
    }
}

void FFSDatabaseInterface::chooseCharacteristicTable()
{
    QString tableName = "characteristic";
    if (actualTable != tableName)
    {
        ui.minorTableView->setModel(nullptr);
        ui.minorSubtableView->setModel(nullptr);
        ui.tableName->setText((tableName + "s:").toUpper());
        ui.minorTableSelector->clear();
        ui.tableSelector->clear();
        ui.minorSubtableView->setDisabled(true);
        ui.minorTableSelector->setDisabled(true);
        ui.tableSelector->setDisabled(true);
        ui.minorTableView->setDisabled(true);
        actualTable = tableName;
        FFSDatabaseInterfaceFormController::ManageShowCharacteristicsTableRequest(ui);
        isRowSelected = false;
    }
}

void FFSDatabaseInterface::openFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName();
    if (filePath != nullptr)
    {
        FFSDatabaseInterfaceFormController::ManageFileImportRequest(filePath);
    }
}

void FFSDatabaseInterface::loadDataToSubtable()
{
    int selectedRow = ui.majorTableView->currentIndex().row();
    QModelIndex indexId = ui.majorTableView->model()->index(selectedRow, 0);
    int selectedId = ui.majorTableView->model()->data(indexId).toInt();
    if (selectedId != this->selectedId || isSubtableChanged)
    {
        ui.minorSubtableView->setModel(nullptr);
        this->selectedId = selectedId;
        isSubtableChanged = false;
        isSubRowSelected = true;
        QString transformedTable = actualTable;
        FFSDatabaseInterfaceFormController::ManageLoadDataToSubtableRequest(ui, ui.minorTableView, transformedTable.replace(' ', '_'), actualSubtable, selectedId);
        actualMinorSubtable = ui.minorTableSelector->currentText().replace(' ', '_').toLower();
        isRowSelected = true;
        if (firstLoad)
        {
            SetTableSettings(ui.minorTableView);
            firstLoad = false;
        }
    }
}

void FFSDatabaseInterface::loadDataToMinorSubtable()
{
    int selectedRow = ui.minorTableView->currentIndex().row();
    QModelIndex indexId = ui.minorTableView->model()->index(selectedRow, 0);
    int selectedId = ui.minorTableView->model()->data(indexId).toInt();
    if (selectedId != this->minorSelectedId || isMinorSubtableChanged)
    {
        this->minorSelectedId = selectedId;
        isMinorSubtableChanged = false;
        QString transformedTable = actualSubtable;
        transformedTable.chop(1);
        FFSDatabaseInterfaceFormController::ManageLoadDataToSubtableRequest(ui, ui.minorSubtableView, transformedTable.replace(' ', '_'), actualMinorSubtable, selectedId);
        isSubRowSelected = true;
        if (minorFirstLoad)
        {
            SetTableSettings(ui.minorSubtableView);
            minorFirstLoad = false;
        }
    }
}

void FFSDatabaseInterface::representTable()
{
    QString newSubtable = ui.tableSelector->currentText().replace(' ', '_').toLower();
    if (newSubtable != actualSubtable)
    {
        isSubtableChanged = true;
        isSubRowSelected = false;
        actualSubtable = newSubtable;
        if (isRowSelected)
        {
            loadDataToSubtable();
        }
    }
}

void FFSDatabaseInterface::representMinorTable()
{
    QString newMinorSubtable = ui.minorTableSelector->currentText().replace(' ', '_').toLower();
    if (newMinorSubtable != actualMinorSubtable)
    {
        isMinorSubtableChanged = true;
        actualMinorSubtable = newMinorSubtable;
        if (isSubRowSelected)
        {
            loadDataToMinorSubtable();
        }
    }
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



