#include "DbContext.h"

DbContext::DbContext()
{
	measurements = QList<MeasurementContext*>();
	measurementParameters = QList<MeasurementParameterContext*>();
	samples = QList<SampleContext*>();
	equipments = QList<EquipmentContext*>();
	equipmentParameters = QList<EquipmentParameterContext*>();
	characteristics = QList<CharacteristicsContext*>();
	characteristicTypes = QList<CharacteristicTypeContext*>();
	bindings = QList<BindingContext*>();
}

DbContext::~DbContext()
{
	qDeleteAll(measurements);
	measurements.clear();
	qDeleteAll(measurementParameters);
	measurementParameters.clear();
	qDeleteAll(samples);
	samples.clear();
	qDeleteAll(equipments);
	equipments.clear();
	qDeleteAll(equipmentParameters);
	equipmentParameters.clear();
	qDeleteAll(characteristics);
	characteristics.clear();
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

void DbContext::AddNewMeasurementParameter(MeasurementParameterContext* measurementParameterContext)
{
	measurementParameters.append(measurementParameterContext);
	measurementParameterContext->IncrementId();
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

void DbContext::AddNewEquipmentParameter(EquipmentParameterContext* equipmentParameterContext)
{
	equipmentParameters.append(equipmentParameterContext);
	equipmentParameterContext->IncrementId();
}

void DbContext::AddNewCharacteristicsSet(CharacteristicsContext* characteristicsContext)
{
	characteristics.append(characteristicsContext);
	characteristicsContext->IncrementId();
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
