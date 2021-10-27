#include "MeasurementAddForm.h"
#include "MeasurementAddFormController.h"

MeasurementAddForm::MeasurementAddForm(QWidget* parent, int fk_measuring_system, int fk_sample) : BaseAddForm(parent)
{
	ui.setupUi(this);
	ui.downButton->setDisabled(true);
	ui.upButton->setDisabled(true);
	ui.AddMeasurementButton->setDisabled(true);
	FFSTableModel* allSamplesTableModel = new FFSTableModel(0, 0);
	FFSTableModel* allMeasuringSystemsTableModel = new FFSTableModel(0, 0);
	FFSTableModel* chosenSamplesTableModel = new FFSTableModel(0, 0);
	FFSTableModel* chosenMeasuringSystemsTableModel = new FFSTableModel(0, 0);
	this->allMeasuringSystemTableModel = allMeasuringSystemsTableModel;
	this->allSamplesTableModel = allSamplesTableModel;
	this->chosenMeasuringSystemsTableModel = chosenMeasuringSystemsTableModel;
	this->chosenSamplesTableModel = chosenSamplesTableModel;

	if (fk_measuring_system == 0 && fk_sample == 0)
	{
		ui.tableSelector->addItem("Measuring systems");
		ui.tableSelector->addItem("Samples");
		ui.allElementsTable->setModel(allMeasuringSystemsTableModel);
		ui.chosenElementsTable->setModel(chosenMeasuringSystemsTableModel);
		MeasurementAddFormController::ManageShowAllElementsTableRequest("samples", ui.allElementsTable, this, true);
		MeasurementAddFormController::ManageShowAllElementsTableRequest("measuring systems", ui.allElementsTable, this, true);
	}
	else
	{
		if (fk_measuring_system == 0)
		{
			this->fk_sample = fk_sample;
			ui.tableSelector->addItem("Measuring systems");
			ui.allElementsTable->setModel(allMeasuringSystemsTableModel);
			ui.chosenElementsTable->setModel(chosenMeasuringSystemsTableModel);
			MeasurementAddFormController::ManageShowAllElementsTableRequest("measuring systems", ui.allElementsTable, this, true);
		}
		else
		{
			this->fk_measuring_system = fk_measuring_system;
			ui.tableSelector->addItem("Samples");
			ui.allElementsTable->setModel(allSamplesTableModel);
			ui.chosenElementsTable->setModel(chosenSamplesTableModel);
			MeasurementAddFormController::ManageShowAllElementsTableRequest("samples", ui.allElementsTable, this, true);
		}
	}


	connect(ui.AddMeasurementButton, SIGNAL(clicked()), this, SLOT(addMeasurement()));
	connect(ui.tableSelector, SIGNAL(activated(QString)), this, SLOT(showAllElementsTable()));
	connect(ui.chosenElementsTable, SIGNAL(clicked(QModelIndex)), this, SLOT(selectChosenElement()));
	connect(ui.allElementsTable, SIGNAL(clicked(QModelIndex)), this, SLOT(selectElement()));
	connect(ui.downButton, SIGNAL(clicked()), this, SLOT(chooseElement()));
	connect(ui.upButton, SIGNAL(clicked()), this, SLOT(cancelChoose()));
	SetTableSettings(ui.allElementsTable);
}

void MeasurementAddForm::addMeasurement()
{
	MeasurementAddFormController::ManageAddMeasurementRequest(this);
	this->close();
}

void MeasurementAddForm::showAllElementsTable()
{
	MeasurementAddFormController::ManageShowAllElementsTableRequest(ui.tableSelector->currentText().toLower(), ui.allElementsTable, this);
}

void MeasurementAddForm::chooseElement()
{
	MeasurementAddFormController::ManageChooseUpperElementRequest(this);
	ui.downButton->setDisabled(true);
}

void MeasurementAddForm::cancelChoose()
{
	MeasurementAddFormController::ManageCancelChooseRequest(this);
	ui.upButton->setDisabled(true);
}

void MeasurementAddForm::selectElement()
{
	if (ui.chosenElementsTable->model()->rowCount() == 0)
	{
		ui.downButton->setDisabled(false);
	}
}

void MeasurementAddForm::selectChosenElement()
{
	ui.upButton->setDisabled(false);
}

FFSTableModel* MeasurementAddForm::GetAllMeasuringSystemsTableModel()
{
	return this->allMeasuringSystemTableModel;
}

FFSTableModel* MeasurementAddForm::GetAllSamplesTableModel()
{
	return this->allSamplesTableModel;
}

FFSTableModel* MeasurementAddForm::GetChosenMeasuringSystemsTableModel()
{
	return this->chosenMeasuringSystemsTableModel;
}

FFSTableModel* MeasurementAddForm::GetChosenSamplesTableModel()
{
	return this->chosenSamplesTableModel;
}

int MeasurementAddForm::GetFKSample()
{
	return this->fk_sample;
}

int MeasurementAddForm::GetFKMeasuringSystem()
{
	return this->fk_measuring_system;
}

bool MeasurementAddForm::GetIsFirstTime()
{
	return this->isFirstTime;
}

void MeasurementAddForm::SetFKMeasuringSystem(int fk_measuring_system)
{
	this->fk_measuring_system = fk_measuring_system;
}

void MeasurementAddForm::SetFKSample(int fk_sample)
{
	this->fk_sample = fk_sample;
}

void MeasurementAddForm::SetIsFirstTime(bool isFirstTime)
{
	this->isFirstTime = isFirstTime;
}

Ui::MeasurementAddFormClass MeasurementAddForm::GetUI()
{
	return this->ui;
}

void MeasurementAddForm::SetTableSettings(QTableView* table)
{
	table->setColumnHidden(0, true);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	table->horizontalHeader()->setStretchLastSection(true);
	table->verticalHeader()->setDefaultSectionSize(20);
	table->verticalHeader()->sectionResizeMode(QHeaderView::Fixed);
	table->setStyleSheet(
		"QHeaderView::section { background-color: rgb(217, 217, 217)}"
		"QTableView {selection-background-color: steelblue}");
}