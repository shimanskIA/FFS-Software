#include "CharacteristicTypeAddForm.h"
#include "CharacteristicTypeAddFormController.h"

CharacteristicTypeAddForm::CharacteristicTypeAddForm(QWidget* parent) : BaseAddForm(parent)
{
	ui.setupUi(this);
	ui.AddCharacteristicTypeButton->setDisabled(true);
	this->setFixedSize(491, 150);
	connect(ui.AddCharacteristicTypeButton, SIGNAL(clicked()), this, SLOT(addCharacteristicType()));
	connect(ui.NameInput, SIGNAL(textChanged(QString)), this, SLOT(manageAddButtonActivity()));
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