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

void DbContext::AddNewMeasurement(MeasurementContext* measurementContext)
{
	measurements.append(measurementContext);
	measurementContext->IncrementId();
}

void DbContext::AddNewSample(SampleContext* sampleContext)
{
	samples.append(sampleContext);
	sampleContext->IncrementId();
}

void DbContext::AddNewEquipment(EquipmentContext* equipmentContext)
{
	equipments.append(equipmentContext);
	equipmentContext->IncrementId();
}

void DbContext::AddNewCharacteristicType(CharacteristicTypeContext* characteristicTypeContext)
{
	characteristicTypes.append(characteristicTypeContext);
	characteristicTypeContext->IncrementId();
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
