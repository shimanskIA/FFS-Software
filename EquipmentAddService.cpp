#include "EquipmentAddService.h"
#include "DbWriter.h"

bool EquipmentAddService::AddEquipmentRequestReceiver(EquipmentContext* equipmentItem)
{
	QVariant tableContext;
	tableContext.setValue<EquipmentContext*>(equipmentItem);
	DbWriter* dbWriter = new DbWriter();
	bool isRowAdded = dbWriter->AddRow(tableContext);

	if (isRowAdded)
	{
		equipmentItem->IncrementId();
		return true;
	}

	return false;
}

void EquipmentAddService::AddExistingEquipmentRequestReceiver(QList<BindingContext*> bindings)
{
	DbWriter* dbWriter = new DbWriter();
	dbWriter->AddBindings(bindings);
}

Q_DECLARE_METATYPE(EquipmentContext*);