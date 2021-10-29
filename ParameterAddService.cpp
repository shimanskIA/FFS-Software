#include "ParameterAddService.h"
#include "DbEditor.h"
#include "NamesHelper.h"
#include "EquipmentParameterContext.h"
#include "MeasurementParameterContext.h"

void ParameterAddService::AddParameterRequestReceiver(ParameterAddForm* view)
{
	QString name = view->GetUI().NameInput->toPlainText();
	QString value = view->GetUI().ValueInput->toPlainText();
	ParameterTableContext* parameter;
	QVariant tableContext;
	int fk = view->GetFK();

	if (view->GetMajorTableName() == "equipment")
	{
		EquipmentParameterContext* equipmentParameter = new EquipmentParameterContext(equipmentParameterStatePath);
		equipmentParameter->SetFKEquipment(fk);
		parameter = equipmentParameter;
		tableContext.setValue<EquipmentParameterContext*>((EquipmentParameterContext*)parameter);
	}
	else
	{
		MeasurementParameterContext* measurementParameter = new MeasurementParameterContext(measurementParametersStatePath);
		measurementParameter->SetFKMeasurement(fk);
		parameter = measurementParameter;
		tableContext.setValue<MeasurementParameterContext*>((MeasurementParameterContext*)parameter);
	}

	parameter->SetName(name);
	parameter->SetValue(value);
	DbEditor* dbEditor = new DbEditor();
	bool isRowAdded = dbEditor->AddRow(tableContext);
	view->SetIsRowAdded(isRowAdded);

	if (isRowAdded)
	{
		parameter->IncrementId();
	}
}

Q_DECLARE_METATYPE(MeasurementParameterContext*);
Q_DECLARE_METATYPE(EquipmentParameterContext*);