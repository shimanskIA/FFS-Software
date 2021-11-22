#pragma once

#include "DbContext.h"
#include "DbConnection.h"
#include "DbReader.h"

class DbWriter
{
public:
	static DbWriter& GetDbWriterInstance();

	bool WriteToDatabase(QString sqlWriteRequest, QString tableName);
	bool AddToDatabase(DbContext* dbContext);

	bool AddSamples(QList<SampleContext*> samples);
	bool AddCharacteristicTypes(QList<CharacteristicTypeContext*> characteristic_types);
	bool AddMeasurementParameters(QList<MeasurementParameterContext*> measurementParameters);
	bool AddEquipmentParameters(QList<EquipmentParameterContext*> equipmentParameters);
	bool AddCharacteristics(QList<CharacteristicsContext*> characteristics);

	bool AddMeasuringSystem(MeasuringSystemContext* measuringSystem);

	bool AddMeasurements(QList<MeasurementContext*> measurements);
	bool AddEquipment(QList<EquipmentContext*> equipments);

	bool AddBindings(QList<BindingContext*> bindings);

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

	void SetInputMeasuringSystemCredentials(QMap<QString, QString> credentials);

private:
	DbWriter() {};
	DbWriter(const DbWriter&) {}

	QMap<QString, QString> inputMeasuringSystemCredentials;

	bool wasEquipmentAdded = false;
};
