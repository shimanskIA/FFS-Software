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

void EquipmentAddService::AddExistingEquipmentRequestReceiver(QList<BindingContext*> bindings)
{
	DbEditor* dbEditor = new DbEditor();
	int fk_measuring_system = bindings.first()->GetFKMeasuringSystem();
	dbEditor->DeleteBindingsWithMeasuringSystem(fk_measuring_system);
	DbWriter* dbWriter = new DbWriter();
	dbWriter->AddBindings(bindings);
}

Q_DECLARE_METATYPE(EquipmentContext*);