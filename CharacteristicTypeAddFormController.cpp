#include "CharacteristicTypeAddFormController.h"
#include "CharacteristicTypeAddService.h"

void CharacteristicTypeAddFormController::ManageAddCharacteristicTypeRequest(CharacteristicTypeAddForm* view)
{
	CharacteristicTypeAddService::AddCharacteristicTypeRequestReceiver(view);
}
