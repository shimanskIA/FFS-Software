#include "CharacteristicTypeAddFormController.h"
#include "CharacteristicTypeAddService.h"
#include "NamesHelper.h"

void CharacteristicTypeAddFormController::ManageAddCharacteristicTypeRequest(CharacteristicTypeAddForm* view)
{
	QString name = view->GetUI().NameInput->toPlainText();
	QString description = view->GetUI().DescriptionInput->toPlainText();
	CharacteristicTypeContext* characteristicType = new CharacteristicTypeContext(characteristicTypeStatePath);
	characteristicType->SetName(name);
	characteristicType->SetDescription(description);
	bool isRowAdded = CharacteristicTypeAddService::AddCharacteristicTypeRequestReceiver(characteristicType);
	view->SetIsRowAdded(isRowAdded);
}
