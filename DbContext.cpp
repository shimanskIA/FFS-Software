#include "DbContext.h"

DbContext::DbContext()
{
	samples = QList<SampleContext*>();
	equipments = QList<EquipmentContext*>();
	characteristicTypes = QList<CharacteristicTypeContext*>();
	measuringSystem = nullptr;
}

DbContext::~DbContext()
{
	qDeleteAll(samples);
	samples.clear();
	qDeleteAll(equipments);
	equipments.clear();
	qDeleteAll(characteristicTypes);
	characteristicTypes.clear();
	delete measuringSystem;
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

void DbContext::SetMeasuringSystem(MeasuringSystemContext* measuringSystem)
{
	this->measuringSystem = measuringSystem;
	measuringSystem->IncrementId();
}

QList<SampleContext*> DbContext::GetSamples()
{
	return this->samples;
}

QList<CharacteristicTypeContext*> DbContext::GetCharacteristicTypes()
{
	return this->characteristicTypes;
}


QList<EquipmentContext*> DbContext::GetEquipments()
{
	return this->equipments;
}

MeasuringSystemContext* DbContext::GetMeasuringSystem()
{
	return this->measuringSystem;
}
