#include "EquipmentAddFormController.h"
#include "EquipmentAddService.h"

void EquipmentAddFormController::ManageAddEquipmentRequest(EquipmentAddForm* view)
{
	EquipmentAddService::AddEquipmentRequestReceiver(view);
}