#include "CharacteristicTypeAddForm.h"
#include "CharacteristicTypeAddFormController.h"

CharacteristicTypeAddForm::CharacteristicTypeAddForm(QWidget* parent) : BaseAddForm(parent)
{
	ui.setupUi(this);
	this->setFixedSize(601, 188);
	connect(ui.AddCharacteristicTypeButton, SIGNAL(clicked()), this, SLOT(addCharacteristicType()));
}

void CharacteristicTypeAddForm::addCharacteristicType()
{
	CharacteristicTypeAddFormController::ManageAddCharacteristicTypeRequest(this);
	this->close();
}

Ui::CharacteristicTypeAddFormClass CharacteristicTypeAddForm::GetUI()
{
	return this->ui;
}