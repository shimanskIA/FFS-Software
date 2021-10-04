#include "DbContext.h"

DbContext::DbContext()
{
	measurements = *(new QList<MeasurementContext>());
	measurementParameters = *(new QList<MeasurementParameterContext>());
	samples = *(new QList<SampleContext>());
	measuringSystems = *(new QList<MeasuringSystemContext>());
	equipments = *(new QList<EquipmentContext>());
	equipmentParameters = *(new QList<EquipmentParameterContext>());
	characteristics = *(new QList<CharacteristicsContext>());
	characteristicTypes = *(new QList<CharacteristicTypeContext>());
	bindings = *(new QList<EquipmentHasMeasuringSystemContext>());
}

DbContext::~DbContext()
{
	delete& measurements;
	delete& measurementParameters;
	delete& samples;
	delete& measuringSystems;
	delete& equipments;
	delete& equipmentParameters;
	delete& characteristics;
	delete& characteristicTypes;
	delete& bindings;
}

void DbContext::AddNewMeasurement(MeasurementContext measurementContext)
{
	measurements.append(measurementContext);
	measurementContext.IncrementId();
}

void DbContext::AddNewMeasurementParameter(MeasurementParameterContext measurementParameterContext)
{
	measurementParameters.append(measurementParameterContext);
	measurementParameterContext.IncrementId();
}

void DbContext::AddNewSample(SampleContext sampleContext)
{
	samples.append(sampleContext);
	sampleContext.IncrementId();
}

void DbContext::AddNewMeasuringSystem(MeasuringSystemContext measuringSystemContext)
{
	measuringSystems.append(measuringSystemContext);
	measuringSystemContext.IncrementId();
}

void DbContext::AddNewEquipment(EquipmentContext equipmentContext)
{
	equipments.append(equipmentContext);
	equipmentContext.IncrementId();
}

void DbContext::AddNewEquipmentParameter(EquipmentParameterContext equipmentParameterContext)
{
	equipmentParameters.append(equipmentParameterContext);
	equipmentParameterContext.IncrementId();
}

void DbContext::AddNewCharacteristicsSet(CharacteristicsContext characteristicsContext)
{
	characteristics.append(characteristicsContext);
	characteristicsContext.IncrementId();
}

void DbContext::AddNewCharacteristicType(CharacteristicTypeContext characteristicTypeContext)
{
	characteristicTypes.append(characteristicTypeContext);
	characteristicTypeContext.IncrementId();
}

void DbContext::AddNewBinding(EquipmentHasMeasuringSystemContext binding)
{
	bindings.append(binding);
}
