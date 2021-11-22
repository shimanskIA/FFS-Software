#include "CharacteristicTypeAddFormController.h"
#include "CharacteristicTypeAddService.h"
#include "NamesHelper.h"
#include "ErrorForm.h"

void CharacteristicTypeAddFormController::ManageAddCharacteristicTypeRequest(CharacteristicTypeAddForm* view)
{
	QString name = view->GetUI().NameInput->toPlainText();
	QString description = view->GetUI().DescriptionInput->toPlainText();
	CharacteristicTypeContext* characteristicType = new CharacteristicTypeContext(characteristicTypeStatePath);
	characteristicType->SetName(name);
	characteristicType->SetDescription(description);
	bool isRowAdded = CharacteristicTypeAddService::AddCharacteristicTypeRequestReceiver(characteristicType);
	view->SetIsRowAdded(isRowAdded);

	if (isRowAdded)
	{
		view->close();
	}
	else
	{
		ErrorForm* errorForm = new ErrorForm("Characteristic type with these name and description already exists.");
		errorForm->show();
		view->GetUI().NameInput->setText("");
	}
}

void CharacteristicTypeAddFormController::ManageAddButtonActivity(CharacteristicTypeAddForm* view)
{
	auto ui = view->GetUI();
	if (ui.NameInput->toPlainText() != "")
	{
		ui.AddCharacteristicTypeButton->setDisabled(false);
	}
	else
	{
		ui.AddCharacteristicTypeButton->setDisabled(true);
	}
}
