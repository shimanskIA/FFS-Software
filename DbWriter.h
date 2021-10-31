#pragma once

#include "DbContext.h"
#include "DbConnection.h"
#include "DbReader.h"

class DbWriter
{
public:
	DbWriter();

	bool WriteToDatabase(QString sqlWriteRequest, QString tableName);
	void AddToDatabase(DbContext* dbContext);

	void AddSamples(QList<SampleContext*> samples);
	void AddCharacteristicTypes(QList<CharacteristicTypeContext*> characteristic_types);
	void AddMeasurementParameters(QList<MeasurementParameterContext*> measurementParameters);
	void AddEquipmentParameters(QList<EquipmentParameterContext*> equipmentParameters);
	void AddCharacteristics(QList<CharacteristicsContext*> characteristics);

	void AddMeasuringSystem(MeasuringSystemContext* measuringSystem);

	void AddMeasurements(QList<MeasurementContext*> measurements);
	void AddEquipment(QList<EquipmentContext*> equipments);

	void AddBindings(QList<BindingContext*> bindings);

	bool AddEquipmentItem(EquipmentContext* equipmentItem);
	bool AddSample(SampleContext* sampleContext, bool isComplex = false);
	bool AddCharacteristicType(CharacteristicTypeContext* characteristicType, bool isComplex = false);
	bool AddMeasurement(MeasurementContext* measurement);
	bool AddCharacteristic(CharacteristicsContext* characteristic);
	bool AddEquipmentParameter(EquipmentParameterContext* equipmentParameter);
	bool AddMeasurementParameter(MeasurementParameterContext* measurementParameter);
	bool AddForwardMeasuringSystem(MeasuringSystemContext* measuringSystem);
	bool AddBinding(BindingContext* binding);

	bool AddRow(QVariant tableContext);

private:
	DbReader* dbReader;

	bool wasEquipmentAdded = false;
};
