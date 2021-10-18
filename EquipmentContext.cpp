#include "EquipmentContext.h"
#include "TextFileInteractionHelper.h"

EquipmentContext::EquipmentContext(QString stateFilePath) : TableContext(stateFilePath)
{
	equipmentParameters = QList<EquipmentParameterContext*>();
}

EquipmentContext::EquipmentContext(int id) : TableContext(id)
{

}

EquipmentContext::~EquipmentContext()
{
	qDeleteAll(equipmentParameters);
	equipmentParameters.clear();
}

void EquipmentContext::SetId(int id)
{
	TableContext::SetId(id);
	ChangeEquipmentParametersFK(id);
}

void EquipmentContext::SetName(QString name)
{
	this->name = name;
}

void EquipmentContext::SetDescription(QString description)
{
	this->description = description;
}

void EquipmentContext::ChangeEquipmentParametersFK(int new_fk)
{
	foreach(EquipmentParameterContext * equipmentParameter, equipmentParameters)
	{
		equipmentParameter->SetFKEquipment(new_fk);
	}
}

void EquipmentContext::AddNewEquipmentParameter(EquipmentParameterContext* equipmentParameter)
{
	equipmentParameters.append(equipmentParameter);
	equipmentParameter->IncrementId();
}

QString EquipmentContext::GetName()
{
	return this->name;
}

QString EquipmentContext::GetDescription()
{
	return this->description;
}

QList<EquipmentParameterContext*> EquipmentContext::GetEquipmentParameters()
{
	return this->equipmentParameters;
}

int EquipmentContext::GetAmountOfEquipmentParameters()
{
	return this->equipmentParameters.length();
}

bool EquipmentContext::ContainsEquipmentParameter(EquipmentParameterContext* equipmentParameter)
{
	QString parameterName = equipmentParameter->GetName();
	QString parameterValue = equipmentParameter->GetValue();

	foreach(EquipmentParameterContext * innerEquipmentParameter, equipmentParameters)
	{
		if (parameterName == innerEquipmentParameter->GetName() && parameterValue == innerEquipmentParameter->GetValue())
		{
			return true;
		}
	}
	return false;
}