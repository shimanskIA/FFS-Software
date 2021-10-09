#include "FFSDatabaseInterface.h"
#include "AboutForm.h"
#include <QFileDialog>
#include "FFSDatabaseInterfaceFormController.h"

FFSDatabaseInterface::FFSDatabaseInterface(QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.actionInfo, SIGNAL(triggered()), this, SLOT(infoButtonClick()));
    connect(ui.actionMeasurment, SIGNAL(triggered()), this, SLOT(chooseMeasurementTable()));
    connect(ui.actionMeasuring_system, SIGNAL(triggered()), this, SLOT(chooseMeasuringSystemTable()));
    connect(ui.actionSample, SIGNAL(triggered()), this, SLOT(chooseSampleTable()));
    connect(ui.actionEquipment, SIGNAL(triggered()), this, SLOT(chooseEquipmentTable()));
    connect(ui.actionImport, SIGNAL(triggered()), this, SLOT(openFileDialog()));
}

void FFSDatabaseInterface::infoButtonClick()
{
    AboutForm* aboutForm = new AboutForm();
    aboutForm->show();
}

void FFSDatabaseInterface::chooseMeasurementTable()
{
    ui.tableName->setText("MEASUREMENT:");
}

void FFSDatabaseInterface::chooseMeasuringSystemTable()
{
    ui.tableName->setText("MEASURING SYSTEM:");
}

void FFSDatabaseInterface::chooseSampleTable()
{
    ui.tableName->setText("SAMPLE:");
}

void FFSDatabaseInterface::chooseEquipmentTable()
{
    ui.tableName->setText("EQUIPMENT:");
}

void FFSDatabaseInterface::openFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName();
    FFSDatabaseInterfaceFormController::ManageFileImportRequest(filePath);
}



