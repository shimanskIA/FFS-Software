#include "EquipmentAddService.h"
#include "DbWriter.h"
#include "DbEditor.h"

bool EquipmentAddService::AddEquipmentRequestReceiver(EquipmentContext* equipmentItem)
{
	QVariant tableContext;
	tableContext.setValue<EquipmentContext*>(equipmentItem);
	bool isRowAdded = DbWriter::GetDbWriterInstance().AddRow(tableContext);

	if (isRowAdded)
	{
		equipmentItem->IncrementId();
		return true;
	}

	return false;
}

void EquipmentAddService::AddExistingEquipmentRequestReceiver(QList<BindingContext*> bindings, int fk_measuring_system)
{
	DbEditor::GetDbEditorInstance().DeleteBindingsWithMeasuringSystem(fk_measuring_system);

	if (!bindings.isEmpty())
	{
		DbWriter::GetDbWriterInstance().AddBindings(bindings);
	}
}

Q_DECLARE_METATYPE(EquipmentContext*);