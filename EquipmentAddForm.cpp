#include "EquipmentAddForm.h"
#include "EquipmentAddFormController.h"

EquipmentAddForm::EquipmentAddForm(QWidget* parent, int fk_measuring_system) : BaseDependentAddForm(parent)
{
	ui.setupUi(this);
	this->setFixedSize(791, 654);
	this->fk_measuring_system = fk_measuring_system;
	ui.allEquipmentTable->setDisabled(true);
	ui.chosenEquipmentTable->setDisabled(true);
	ui.downButton->setDisabled(true);
	ui.upButton->setDisabled(true);

	if (fk_measuring_system != 0)
	{
		allEquipmentTableModel = new FFSTableModel(0, 0);
		ui.allEquipmentTable->setModel(allEquipmentTableModel);
		chosenEquipmentTableModel = new FFSTableModel(0, 0);
		ui.chosenEquipmentTable->setModel(chosenEquipmentTableModel);
		connect(ui.chosenEquipmentTable, SIGNAL(clicked(QModelIndex)), this, SLOT(selectChosenElement()));
		connect(ui.allEquipmentTable, SIGNAL(clicked(QModelIndex)), this, SLOT(selectElement()));
		connect(ui.downButton, SIGNAL(clicked()), this, SLOT(chooseElement()));
		connect(ui.upButton, SIGNAL(clicked()), this, SLOT(cancelChoose()));
		connect(ui.addExistingEquipmentCheckbox, SIGNAL(stateChanged(int)), this, SLOT(chooseExistingEquipment(int)));
		connect(ui.allEquipmentTable->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortAllElementsTableRows(int)));
		connect(ui.chosenEquipmentTable->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortChosenElementsTableRows(int)));
	}

	connect(ui.AddEquipmentButton, SIGNAL(clicked()), this, SLOT(addEquipment()));
}

EquipmentAddForm::~EquipmentAddForm()
{
	delete allEquipmentTableModel;
	delete chosenEquipmentTableModel;
}

void EquipmentAddForm::sortAllElementsTableRows(int selectedColumn)
{
	EquipmentAddFormController::ManageSortRowsRequest(ui.allEquipmentTable, selectedColumn);
}

void EquipmentAddForm::sortChosenElementsTableRows(int selectedColumn)
{
	EquipmentAddFormController::ManageSortRowsRequest(ui.chosenEquipmentTable, selectedColumn);
}

void EquipmentAddForm::addEquipment()
{
	if (isExistingEquipmentChosen)
	{
		EquipmentAddFormController::ManageAddExistingEquipmentRequest(this, fk_measuring_system);
	}
	else
	{
		EquipmentAddFormController::ManageAddEquipmentRequest(this);
	}

	this->close();
}

void EquipmentAddForm::chooseExistingEquipment(int checkboxState)
{
	EquipmentAddFormController::ManageChooseExistingEquipmentRequest(this, checkboxState);
}

void EquipmentAddForm::showAllElementsTable()
{
	EquipmentAddFormController::ManageShowAllElementsTableRequest(ui.allEquipmentTable);
}

void EquipmentAddForm::chooseElement()
{
	EquipmentAddFormController::ManageChooseUpperElementRequest(this);

	if (ui.allEquipmentTable->model()->rowCount() == 0)
	{
		ui.downButton->setDisabled(true);
	}
}

void EquipmentAddForm::cancelChoose()
{
	EquipmentAddFormController::ManageCancelChooseRequest(this);

	if (ui.chosenEquipmentTable->model()->rowCount() == 0)
	{
		ui.upButton->setDisabled(true);
	}
}

void EquipmentAddForm::selectElement()
{
	ui.downButton->setDisabled(false);
}

void EquipmentAddForm::selectChosenElement()
{
	ui.upButton->setDisabled(false);
}

int EquipmentAddForm::GetFKMeasuringSystem()
{
	return this->fk_measuring_system;
}

FFSTableModel* EquipmentAddForm::GetAllEquipmentTableModel()
{
	return this->allEquipmentTableModel;
}

FFSTableModel* EquipmentAddForm::GetChosenEquipmentTableModel()
{
	return this->chosenEquipmentTableModel;
}

bool EquipmentAddForm::GetIsExistingEquipmentChosen()
{
	return this->isExistingEquipmentChosen;
}

bool EquipmentAddForm::GetIsFirstTime()
{
	return this->isFirstTime;
}

Ui::EquipmentAddFormClass EquipmentAddForm::GetUI()
{
	return this->ui;
}

void EquipmentAddForm::SetIsExistingEquipmentChosen(bool isExistingEquipmentChosen)
{
	this->isExistingEquipmentChosen = isExistingEquipmentChosen;
}

void EquipmentAddForm::SetIsFirstTime(bool isFirstTime)
{
	this->isFirstTime = isFirstTime;
}