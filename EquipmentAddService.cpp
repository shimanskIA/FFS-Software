#include "EquipmentAddService.h"
#include "DbEditor.h"

bool EquipmentAddService::AddEquipmentRequestReceiver(EquipmentContext* equipmentItem)
{
	QVariant tableContext;
	tableContext.setValue<EquipmentContext*>(equipmentItem);
	DbEditor* dbEditor = new DbEditor();
	bool isRowAdded = dbEditor->AddRow(tableContext);

	if (isRowAdded)
	{
		equipmentItem->IncrementId();
		return true;
	}

	return false;
}

Q_DECLARE_METATYPE(EquipmentContext*);