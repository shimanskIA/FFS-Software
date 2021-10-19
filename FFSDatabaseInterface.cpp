#include "FFSDatabaseInterface.h"
#include "AboutForm.h"
#include "ui_AboutForm.h"
#include "FFSDatabaseInterfaceFormController.h"

#include <QFileDialog>

FFSDatabaseInterface::FFSDatabaseInterface(QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.actionInfo, SIGNAL(triggered()), this, SLOT(infoButtonClick()));
    connect(ui.actionMeasurment, SIGNAL(triggered()), this, SLOT(chooseMeasurementTable()));
    connect(ui.actionSample, SIGNAL(triggered()), this, SLOT(chooseSampleTable()));
    connect(ui.actionEquipment, SIGNAL(triggered()), this, SLOT(chooseEquipmentTable()));
    connect(ui.actionImport, SIGNAL(triggered()), this, SLOT(openFileDialog()));
    connect(ui.majorTableView, SIGNAL(clicked(QModelIndex)), this, SLOT(loadDataToSubtable()));
    FFSDatabaseInterfaceFormController::ManageShowMeasurementTableRequest(ui);
    ui.tableSelector->addItem("Measurement parameters");
    ui.tableSelector->addItem("Characteristics");
    ui.tableSelector->addItem("Equipments");
    ui.tableName->setText((actualTable + ":").toUpper());
    SetTableSettings(ui.majorTableView);
}

void FFSDatabaseInterface::infoButtonClick()
{
    AboutForm* aboutForm = new AboutForm();
    aboutForm->show();
}

void FFSDatabaseInterface::chooseMeasurementTable()
{
    QString tableName = "measurements";
    if (actualTable != tableName)
    {
        ui.tableName->setText((tableName + ":").toUpper());
        ui.tableSelector->clear();
        ui.tableSelector->addItem("Measurement parameters");
        ui.tableSelector->addItem("Characteristics");
        ui.tableSelector->addItem("Equipments");
        actualTable = tableName;
        FFSDatabaseInterfaceFormController::ManageShowMeasurementTableRequest(ui);
    }
}

void FFSDatabaseInterface::chooseSampleTable()
{
    QString tableName = "samples";
    if (actualTable != tableName)
    {
        ui.tableName->setText((tableName + ":").toUpper());
        ui.tableSelector->clear();
        ui.tableSelector->addItem("Measurements");
        actualTable = tableName;
        FFSDatabaseInterfaceFormController::ManageShowSampleTableRequest(ui);
    }
}

void FFSDatabaseInterface::chooseEquipmentTable()
{
    QString tableName = "equipments";
    if (actualTable != tableName)
    {
        ui.tableName->setText((tableName + ":").toUpper());
        ui.tableSelector->clear();
        ui.tableSelector->addItem("Equipment parameters");
        ui.tableSelector->addItem("Measurements");
        actualTable = tableName;
        FFSDatabaseInterfaceFormController::ManageShowEquipmentTableRequest(ui);
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
    if (selectedId != this->selectedId)
    {
        this->selectedId = selectedId;
        FFSDatabaseInterfaceFormController::ManageLoadDataToSubtableRequest(ui, actualTable, actualSubtable, selectedId);
        if (firstLoad)
        {
            SetTableSettings(ui.minorTableView);
            firstLoad = false;
        }
    }
    
}

void FFSDatabaseInterface::SetTableSettings(QTableView* table)
{
    table->setColumnHidden(0, true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::DoubleClicked);
    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setDefaultSectionSize(20);
    table->verticalHeader()->sectionResizeMode(QHeaderView::Fixed);
    table->setStyleSheet(
        "QHeaderView::section { background-color: rgb(217, 217, 217)}"
        "QTableView {selection-background-color: steelblue}");
}



