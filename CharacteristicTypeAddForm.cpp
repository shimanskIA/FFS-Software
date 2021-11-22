#include "CharacteristicTypeAddForm.h"
#include "CharacteristicTypeAddFormController.h"

CharacteristicTypeAddForm::CharacteristicTypeAddForm(QWidget* parent) : BaseAddForm(parent)
{
	ui.setupUi(this);
	ui.AddCharacteristicTypeButton->setDisabled(true);
	this->setFixedSize(601, 188);
	connect(ui.AddCharacteristicTypeButton, SIGNAL(clicked()), this, SLOT(addCharacteristicType()));
	connect(ui.NameInput, SIGNAL(textChanged()), this, SLOT(manageAddButtonActivity()));
}

void CharacteristicTypeAddForm::manageAddButtonActivity()
{
	CharacteristicTypeAddFormController::ManageAddButtonActivity(this);
}

void CharacteristicTypeAddForm::addCharacteristicType()
{
	CharacteristicTypeAddFormController::ManageAddCharacteristicTypeRequest(this);
}

Ui::CharacteristicTypeAddFormClass CharacteristicTypeAddForm::GetUI()
{
	return this->ui;
}