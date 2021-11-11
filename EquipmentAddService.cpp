#include "EquipmentAddService.h"
#include "DbWriter.h"
#include "DbEditor.h"

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

void EquipmentAddService::AddExistingEquipmentRequestReceiver(QList<BindingContext*> bindings, int fk_measuring_system)
{
	DbEditor* dbEditor = new DbEditor();
	dbEditor->DeleteBindingsWithMeasuringSystem(fk_measuring_system);
	DbWriter* dbWriter = new DbWriter();

	if (!bindings.isEmpty())
	{
		dbWriter->AddBindings(bindings);
	}
}

Q_DECLARE_METATYPE(EquipmentContext*);