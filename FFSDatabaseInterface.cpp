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
    FFSDatabaseInterfaceFormController::ManageShowMeasurementTableRequest(ui);
}

void FFSDatabaseInterface::infoButtonClick()
{
    AboutForm* aboutForm = new AboutForm();
    aboutForm->show();
}

void FFSDatabaseInterface::chooseMeasurementTable()
{
    ui.tableName->setText("MEASUREMENT:");
    FFSDatabaseInterfaceFormController::ManageShowMeasurementTableRequest(ui);
}

void FFSDatabaseInterface::chooseSampleTable()
{
    ui.tableName->setText("SAMPLE:");
    FFSDatabaseInterfaceFormController::ManageShowSampleTableRequest(ui);
}

void FFSDatabaseInterface::chooseEquipmentTable()
{
    ui.tableName->setText("EQUIPMENT:");
    FFSDatabaseInterfaceFormController::ManageShowEquipmentTableRequest(ui);
}

void FFSDatabaseInterface::openFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName();
    if (filePath != nullptr)
    {
        FFSDatabaseInterfaceFormController::ManageFileImportRequest(filePath);
    }
}



