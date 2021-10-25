#pragma once

#include <QtSql>
#include <QSqlDatabase>
#include <QList>

#include "DbContext.h"

class DbConnection
{
public:
	static DbConnection& GetDbConnectionInstance();
	void AddToDatabase(DbContext* dbContext);
	void DeleteFromDatabase(QString tableName, int id);
	void UpdateDatabase(QString tableName, QString columnName, QString cellValue, int id);
	QSqlQuery ReadFromDatabase(QString sqlRequest);
	bool WriteToDatabase(QString sqlWriteRequest, QString tableName);

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

	QList<MeasuringSystemContext*> ReadMeasuringSystemsFromDatabase();
	QList<MeasurementContext*> ReadMeasurementsFromDatabase();
	QList<MeasurementContext*> ReadMeasurementsFromDatabase(QString majortableName, int fk);
	QList<SampleContext*> ReadSamplesFromDatabase();
	QList<EquipmentContext*> ReadEquipmentsFromDatabase();
	QList<CharacteristicsContext*> ReadCharacteristicsFromDatabase(QString sqlReadRequest);
	QList<CharacteristicTypeContext*> ReadCharacteristicTypesFromDatabase();
	QList<BindingContext*> ReadBindingsFromDatabase(QString majorTableName, int fk);
	QList<ParameterTableContext*> ReadParametersFromDatabase(QString majorTableName, QString minorTableName, int fk);

private:
	DbConnection();
	DbConnection(const DbConnection&) {}
	QSqlDatabase database;

	bool wasEquipmentAdded = false;
};




