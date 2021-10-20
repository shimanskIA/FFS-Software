#include "MeasuringSystemContext.h"

MeasuringSystemContext::MeasuringSystemContext(QString fileLink) : TableContext(fileLink)
{
	bindings = QList<BindingContext*>();
	measurements = QList<MeasurementContext*>();
}

MeasuringSystemContext::~MeasuringSystemContext()
{
	qDeleteAll(bindings);
	bindings.clear();
	qDeleteAll(measurements);
	measurements.clear();
}

void MeasuringSystemContext::SetId(int id)
{
	TableContext::SetId(id);
}

void MeasuringSystemContext::SetName(QString name)
{
	this->name = name;
}

void MeasuringSystemContext::SetDescription(QString description)
{
	this->description = description;
}

void MeasuringSystemContext::SetMainContributorName(QString mainContributorName)
{
	this->mainContributorName = mainContributorName;
}

void MeasuringSystemContext::AddNewBinding(BindingContext* binding)
{
	this->bindings.append(binding);
}

void MeasuringSystemContext::AddNewMeasurement(MeasurementContext* measurement)
{
	this->measurements.append(measurement);
	measurement->IncrementId();
}

QString MeasuringSystemContext::GetName()
{
	return this->name;
}

QString MeasuringSystemContext::GetDescription()
{
	return this->description;
}

QString MeasuringSystemContext::GetMainContributorName()
{
	return this->mainContributorName;
}

QList<BindingContext*> MeasuringSystemContext::GetBindings()
{
	return this->bindings;
}

QList<MeasurementContext*> MeasuringSystemContext::GetMeasurements()
{
	return this->measurements;
}

int MeasuringSystemContext::GetAmountOfBindings()
{
	return this->bindings.length();
}

bool MeasuringSystemContext::ContainsBindingWithThisEquipment(int equipmentId)
{
	foreach(BindingContext* binding, bindings)
	{
		if (binding->GetFKEquipment() == equipmentId)
		{
			return true;
		}
	}
	return false;
}

void MeasuringSystemContext::ChangeBindingsFK(int new_fk)
{
	foreach(BindingContext * binding, bindings)
	{
		binding->SetFKMeasuringSystem(new_fk);
	}
}

void MeasuringSystemContext::ChangeMeasurementsFK(int new_fk)
{
	foreach(MeasurementContext * measurement, measurements)
	{
		measurement->SetFKMeasuringSystem(new_fk);
	}
}