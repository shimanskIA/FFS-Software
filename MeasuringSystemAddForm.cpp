#include "MeasuringSystemAddForm.h"
#include "MeasuringSystemAddFormController.h"

MeasuringSystemAddForm::MeasuringSystemAddForm(QWidget* parent) : BaseDependentAddForm(parent)
{
	ui.setupUi(this);
	this->setFixedSize(791, 755);
	ui.downButton->setDisabled(true);
	ui.upButton->setDisabled(true);
	ui.AddMeasuringSystemButton->setDisabled(true);
	ui.allElementsTable->setModel(new FFSTableModel(0, 0));
	ui.chosenElementsTable->setModel(new FFSTableModel(0, 0));
	ui.tableSelector->addItem("Equipment");
	MeasuringSystemAddFormController::ManageShowAllElementsTableRequest(ui.allElementsTable);
	connect(ui.AddMeasuringSystemButton, SIGNAL(clicked()), this, SLOT(addMeasuringSystem()));
	connect(ui.tableSelector, SIGNAL(activated(QString)), this, SLOT(showAllElementsTable()));
	connect(ui.chosenElementsTable, SIGNAL(clicked(QModelIndex)), this, SLOT(selectChosenElement()));
	connect(ui.allElementsTable, SIGNAL(clicked(QModelIndex)), this, SLOT(selectElement()));
	connect(ui.downButton, SIGNAL(clicked()), this, SLOT(chooseElement()));
	connect(ui.upButton, SIGNAL(clicked()), this, SLOT(cancelChoose()));
	connect(ui.allElementsTable->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortAllElementsTableRows(int)));
	connect(ui.chosenElementsTable->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortChosenElementsTableRows(int)));
	connect(ui.NameInput, SIGNAL(textChanged(QString)), this, SLOT(manageAddButtonActivity()));
	connect(ui.MainContributorNameInput, SIGNAL(textChanged(QString)), this, SLOT(manageAddButtonActivity()));
	SetTableSettings(ui.allElementsTable);
}

void MeasuringSystemAddForm::sortAllElementsTableRows(int selectedColumn)
{
	MeasuringSystemAddFormController::ManageSortRowsRequest(ui.allElementsTable, selectedColumn);
}

void MeasuringSystemAddForm::sortChosenElementsTableRows(int selectedColumn)
{
	MeasuringSystemAddFormController::ManageSortRowsRequest(ui.chosenElementsTable, selectedColumn);
}

void MeasuringSystemAddForm::addMeasuringSystem()
{
	MeasuringSystemAddFormController::ManageAddMeasuringSystemRequest(this);
}

void MeasuringSystemAddForm::showAllElementsTable()
{
	MeasuringSystemAddFormController::ManageShowAllElementsTableRequest(ui.allElementsTable);
}

void MeasuringSystemAddForm::manageAddButtonActivity()
{
	MeasuringSystemAddFormController::ManageAddButtonActivity(this);
}

void MeasuringSystemAddForm::chooseElement()
{
	MeasuringSystemAddFormController::ManageChooseUpperElementRequest(this);

	if (ui.allElementsTable->model()->rowCount() == 0)
	{
		ui.downButton->setDisabled(true);
	}
}

void MeasuringSystemAddForm::cancelChoose()
{
	MeasuringSystemAddFormController::ManageCancelChooseRequest(this);

	if (ui.chosenElementsTable->model()->rowCount() == 0)
	{
		ui.upButton->setDisabled(true);
	}
}

void MeasuringSystemAddForm::selectElement()
{
	ui.downButton->setDisabled(false);
}

void MeasuringSystemAddForm::selectChosenElement()
{
	ui.upButton->setDisabled(false);
}

bool MeasuringSystemAddForm::GetIsFirstTime()
{
	return this->isFirstTime;
}

void MeasuringSystemAddForm::SetIsFirstTime(bool isFirstTime)
{
	this->isFirstTime = isFirstTime;
}

Ui::MeasuringSystemAddFormClass MeasuringSystemAddForm::GetUI()
{
	return this->ui;
}