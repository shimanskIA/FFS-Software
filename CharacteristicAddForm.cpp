#include "CharacteristicAddForm.h"
#include "CharacteristicAddFormController.h"

CharacteristicAddForm::CharacteristicAddForm(QWidget* parent, int fk_measurement, int fk_characteristic_type) : BaseDependentAddForm(parent)
{
	ui.setupUi(this);
	ui.downButton->setDisabled(true);
	ui.upButton->setDisabled(true);
	ui.AddCharacteristicButton->setDisabled(true);
	ui.ChannelInput->setMaxLength(100);
	ui.XInput->setMaxLength(8000);
	ui.YInput->setMaxLength(8000);
	FFSTableModel* allMeasurementsTableModel = new FFSTableModel(0, 0);
	FFSTableModel* allCharacteristicTypesTableModel = new FFSTableModel(0, 0);
	FFSTableModel* chosenMeasurementsTableModel = new FFSTableModel(0, 0);
	FFSTableModel* chosenCharacteristicTypesTableModel = new FFSTableModel(0, 0);
	this->allMeasurementsTableModel = allMeasurementsTableModel;
	this->allCharacteristicTypesTableModel = allCharacteristicTypesTableModel;
	this->chosenMeasurementsTableModel = chosenMeasurementsTableModel;
	this->chosenCharacteristicTypesTableModel = chosenCharacteristicTypesTableModel;

	if (fk_measurement == 0 && fk_characteristic_type == 0)
	{
		ui.tableSelector->addItem("Measurements");
		ui.tableSelector->addItem("Characteristic types");
		ui.allElementsTable->setModel(allMeasurementsTableModel);
		ui.chosenElementsTable->setModel(chosenMeasurementsTableModel);
		CharacteristicAddFormController::ManageShowAllElementsTableRequest("characteristic types", ui.allElementsTable, this, true);
		CharacteristicAddFormController::ManageShowAllElementsTableRequest("measurements", ui.allElementsTable, this, true);
	}
	else
	{
		if (fk_measurement == 0)
		{
			this->fk_characteristic_type = fk_characteristic_type;
			ui.tableSelector->addItem("Measurements");
			ui.allElementsTable->setModel(allMeasurementsTableModel);
			ui.chosenElementsTable->setModel(chosenMeasurementsTableModel);
			CharacteristicAddFormController::ManageShowAllElementsTableRequest("measurements", ui.allElementsTable, this, true);
		}
		else
		{
			this->fk_measurement = fk_measurement;
			ui.tableSelector->addItem("Characteristic types");
			ui.allElementsTable->setModel(allCharacteristicTypesTableModel);
			ui.chosenElementsTable->setModel(chosenCharacteristicTypesTableModel);
			CharacteristicAddFormController::ManageShowAllElementsTableRequest("characteristic types", ui.allElementsTable, this, true);
		}
	}


	connect(ui.AddCharacteristicButton, SIGNAL(clicked()), this, SLOT(addCharacteristic()));
	connect(ui.tableSelector, SIGNAL(activated(QString)), this, SLOT(showAllElementsTable()));
	connect(ui.chosenElementsTable, SIGNAL(clicked(QModelIndex)), this, SLOT(selectChosenElement()));
	connect(ui.allElementsTable, SIGNAL(clicked(QModelIndex)), this, SLOT(selectElement()));
	connect(ui.downButton, SIGNAL(clicked()), this, SLOT(chooseElement()));
	connect(ui.upButton, SIGNAL(clicked()), this, SLOT(cancelChoose()));
	connect(ui.ChannelInput, SIGNAL(textChanged(QString)), this, SLOT(manageAddButtonActivity()));
	connect(ui.XInput, SIGNAL(textChanged(QString)), this, SLOT(manageAddButtonActivity()));
	connect(ui.YInput, SIGNAL(textChanged(QString)), this, SLOT(manageAddButtonActivity()));
	connect(ui.allElementsTable->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortAllElementsTableRows(int)));
	connect(ui.chosenElementsTable->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortChosenElementsTableRows(int)));
	SetTableSettings(ui.allElementsTable);
}

CharacteristicAddForm::~CharacteristicAddForm()
{
	delete allCharacteristicTypesTableModel;
	delete chosenCharacteristicTypesTableModel;
	delete allMeasurementsTableModel;
	delete chosenMeasurementsTableModel;
}

void CharacteristicAddForm::sortAllElementsTableRows(int selectedColumn)
{
	CharacteristicAddFormController::ManageSortRowsRequest(ui.allElementsTable, selectedColumn);
}

void CharacteristicAddForm::sortChosenElementsTableRows(int selectedColumn)
{
	CharacteristicAddFormController::ManageSortRowsRequest(ui.chosenElementsTable, selectedColumn);
}

void CharacteristicAddForm::addCharacteristic()
{
	CharacteristicAddFormController::ManageAddCharacteristicRequest(this);
	this->close();
}

void CharacteristicAddForm::manageAddButtonActivity()
{
	CharacteristicAddFormController::ManageAddButtonActivity(this);
}

void CharacteristicAddForm::showAllElementsTable()
{
	CharacteristicAddFormController::ManageShowAllElementsTableRequest(ui.tableSelector->currentText().toLower(), ui.allElementsTable, this);
}

void CharacteristicAddForm::chooseElement()
{
	CharacteristicAddFormController::ManageChooseUpperElementRequest(this);
	ui.downButton->setDisabled(true);
}

void CharacteristicAddForm::cancelChoose()
{
	CharacteristicAddFormController::ManageCancelChooseRequest(this);
	ui.upButton->setDisabled(true);
}

void CharacteristicAddForm::selectElement()
{
	if (ui.chosenElementsTable->model()->rowCount() == 0)
	{
		ui.downButton->setDisabled(false);
	}
}

void CharacteristicAddForm::selectChosenElement()
{
	ui.upButton->setDisabled(false);
}

FFSTableModel* CharacteristicAddForm::GetAllMeasurementsTableModel()
{
	return this->allMeasurementsTableModel;
}

FFSTableModel* CharacteristicAddForm::GetAllCharacteristicTypesTableModel()
{
	return this->allCharacteristicTypesTableModel;
}

FFSTableModel* CharacteristicAddForm::GetChosenMeasurementsTableModel()
{
	return this->chosenMeasurementsTableModel;
}

FFSTableModel* CharacteristicAddForm::GetChosenCharacteristicTypesTableModel()
{
	return this->chosenCharacteristicTypesTableModel;
}

int CharacteristicAddForm::GetFKMeasurement()
{
	return this->fk_measurement;
}

int CharacteristicAddForm::GetFKCharacteristicType()
{
	return this->fk_characteristic_type;
}

bool CharacteristicAddForm::GetIsFirstTime()
{
	return this->isFirstTime;
}

void CharacteristicAddForm::SetFKMeasurement(int fk_measurement)
{
	this->fk_measurement = fk_measurement;
}

void CharacteristicAddForm::SetFKCharacteristicType(int fk_characteristic_type)
{
	this->fk_characteristic_type = fk_characteristic_type;
}

void CharacteristicAddForm::SetIsFirstTime(bool isFirstTime)
{
	this->isFirstTime = isFirstTime;
}

Ui::CharacteristicAddFormClass CharacteristicAddForm::GetUI()
{
	return this->ui;
}