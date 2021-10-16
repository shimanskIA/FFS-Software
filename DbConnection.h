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
	QSqlQuery ReadFromDatabase(QString sqlRequest);
	void WriteToDatabase(QString sqlWriteRequest, QString tableName);
	void AddSamples(QList<SampleContext*> samples);
	void AddCharacteristicTypes(QList<CharacteristicTypeContext*> characteristic_types);
	void AddMeasurementParameters(QList<MeasurementParameterContext*> measurementParameters);
	void AddEquipmentParameters(QList<EquipmentParameterContext*> equipmentParameters);
	void AddCharacteristics(QList<CharacteristicsContext*> characteristics);

	void AddMeasurements(QList<MeasurementContext*> measurements, DbContext* dbContext);
	void AddEquipment(QList<EquipmentContext*> equipments, DbContext* dbContext);

	void AddBindings(QList<BindingContext*> bindings);

private:
	DbConnection();
	DbConnection(const DbConnection&) {}
	QSqlDatabase database;
};




