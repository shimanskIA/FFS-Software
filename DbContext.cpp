#include "DbContext.h"

DbContext::DbContext()
{
	measurements = QList<MeasurementContext*>();
	samples = QList<SampleContext*>();
	equipments = QList<EquipmentContext*>();
	characteristicTypes = QList<CharacteristicTypeContext*>();
	bindings = QList<BindingContext*>();
}

DbContext::~DbContext()
{
	qDeleteAll(measurements);
	measurements.clear();
	qDeleteAll(samples);
	samples.clear();
	qDeleteAll(equipments);
	equipments.clear();
	qDeleteAll(characteristicTypes);
	characteristicTypes.clear();
	qDeleteAll(bindings);
	bindings.clear();
}

void DbContext::AddNewMeasurement(MeasurementContext* measurement)
{
	measurements.append(measurement);
	measurement->IncrementId();
}

void DbContext::AddNewSample(SampleContext* sample)
{
	samples.append(sample);
	sample->IncrementId();
}

void DbContext::AddNewEquipment(EquipmentContext* equipment)
{
	equipments.append(equipment);
	equipment->IncrementId();
}

void DbContext::AddNewCharacteristicType(CharacteristicTypeContext* characteristicType)
{
	characteristicTypes.append(characteristicType);
	characteristicType->IncrementId();
}

void DbContext::AddNewBinding(BindingContext* binding)
{
	bindings.append(binding);
}

QList<SampleContext*> DbContext::GetSamples()
{
	return this->samples;
}

QList<CharacteristicTypeContext*> DbContext::GetCharacteristicTypes()
{
	return this->characteristicTypes;
}

QList<MeasurementContext*> DbContext::GetMeasurements()
{
	return this->measurements;
}

QList<EquipmentContext*> DbContext::GetEquipments()
{
	return this->equipments;
}

QList<BindingContext*> DbContext::GetBindings()
{
	return this->bindings;
}
