#include "EquipmentAddFormController.h"
#include "EquipmentAddService.h"
#include "NamesHelper.h"

void EquipmentAddFormController::ManageAddEquipmentRequest(EquipmentAddForm* view)
{
	QString name = view->GetUI().NameInput->toPlainText();
	QString description = view->GetUI().DescriptionInput->toPlainText();
	EquipmentContext* equipmentItem = new EquipmentContext(equipmentStatePath);
	equipmentItem->SetName(name);
	equipmentItem->SetDescription(description);
	bool isRowAdded =  EquipmentAddService::AddEquipmentRequestReceiver(equipmentItem);
	view->SetIsRowAdded(isRowAdded);
}