#include "ParameterAddFormController.h"
#include "ParameterAddService.h"
#include "EquipmentParameterContext.h"
#include "MeasurementParameterContext.h"
#include "NamesHelper.h"

void ParameterAddFormController::ManageAddParameterRequest(ParameterAddForm* view)
{
	QString name = view->GetUI().NameInput->toPlainText();
	QString value = view->GetUI().ValueInput->toPlainText();
	ParameterTableContext* parameter;
	QVariant tableContext;
	int fk = view->GetFK();
	bool isRowAdded = false;

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
	isRowAdded = ParameterAddService::AddParameterRequestReceiver(tableContext);

	if (isRowAdded)
	{
		parameter->IncrementId();
	}
	else
	{
		ErrorForm* errorForm = new ErrorForm("It was unable to add parameter because it already exists in database.");
		errorForm->setWindowFlags(Qt::WindowStaysOnTopHint);
		errorForm->show();
	}

	view->SetIsRowAdded(isRowAdded);
}

Q_DECLARE_METATYPE(MeasurementParameterContext*);
Q_DECLARE_METATYPE(EquipmentParameterContext*);