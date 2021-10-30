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

	if (view->GetFKMeasuringSystem() != 0)
	{
		BindingContext* binding = new BindingContext();
		binding->SetFKMeasuringSystem(view->GetFKMeasuringSystem());
		binding->SetFKEquipment(equipmentItem->GetId());
		equipmentItem->SetBinding(binding);
	}

	bool isRowAdded =  EquipmentAddService::AddEquipmentRequestReceiver(equipmentItem);
	view->SetIsRowAdded(isRowAdded);
}