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
    connect(ui.minorSubtableView, SIGNAL(clicked(QModelIndex)), this, SLOT(switchButtons()));
    connect(ui.tableSelector, SIGNAL(activated(QString)), this, SLOT(representTable()));
    connect(ui.minorTableSelector, SIGNAL(activated(QString)), this, SLOT(representMinorTable()));
    FFSDatabaseInterfaceFormController::ManageShowMeasuringSystemTableRequest(this, true);
    SetTableSettings(ui.majorTableView);
}

void FFSDatabaseInterface::infoButtonClick()
{
    AboutForm* aboutForm = new AboutForm();
    aboutForm->show();
}

void FFSDatabaseInterface::chooseMeasuringSystemTable()
{
    FFSDatabaseInterfaceFormController::ManageShowMeasuringSystemTableRequest(this);
}

void FFSDatabaseInterface::chooseMeasurementTable()
{
    FFSDatabaseInterfaceFormController::ManageShowMeasurementTableRequest(this);
}

void FFSDatabaseInterface::chooseSampleTable()
{
    FFSDatabaseInterfaceFormController::ManageShowSampleTableRequest(this);
}

void FFSDatabaseInterface::chooseEquipmentTable()
{
    FFSDatabaseInterfaceFormController::ManageShowEquipmentTableRequest(this);
}

void FFSDatabaseInterface::chooseCharacteristicTypeTable()
{
    FFSDatabaseInterfaceFormController::ManageShowCharacteristicTypesTableRequest(this);
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

int FFSDatabaseInterface::GetSelectedId()
{
    return this->selectedId;
}

int FFSDatabaseInterface::GetMinorSelectedId()
{
    return this->minorSelectedId;
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

void FFSDatabaseInterface::SetSelectedId(int selectedId)
{
    this->selectedId = selectedId;
}

void FFSDatabaseInterface::SetMinorSelectedId(int minorSelectedId)
{
    this->minorSelectedId = minorSelectedId;
}