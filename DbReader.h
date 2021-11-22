#pragma once

#include "DbContext.h"
#include "DbConnection.h"
#include "OperationStatusMessage.h"

#include <QString>
#include <QtSql>

class DbReader
{
public:
	static DbReader& GetDbReaderInstance();

	QSqlQuery ReadFromDatabase(QString sqlRequest);

	OperationStatusMessage* ReadAbscissaFromDatabase(int characteristicId, QVector<double>& x);
	OperationStatusMessage* ReadOrdinateFromDatabase(int characteristicId, QVector<double>& y);

	QList<MeasuringSystemContext*> ReadMeasuringSystemsFromDatabase();
	QList<MeasurementContext*> ReadMeasurementsFromDatabase();
	QList<MeasurementContext*> ReadMeasurementsFromDatabase(QString majortableName, int fk);
	QList<SampleContext*> ReadSamplesFromDatabase();
	QList<EquipmentContext*> ReadEquipmentsFromDatabase();
	QList<EquipmentContext*> ReadExistingEquipmentFromDatabase(int fk_measuring_system);
	QList<EquipmentContext*> ReadBindedEquipmentFromDatabase(int fk_measuring_system);
	QList<EquipmentContext*> ReadEquipmentOfSpecificTypeFromDatabase(QString name);
	QList<CharacteristicsContext*> ReadCharacteristicsFromDatabase();
	QList<CharacteristicsContext*> ReadCharacteristicsFromDatabase(QString majorTableName, int fk);
	QList<CharacteristicsContext*> ReadCharacteristicsFromDatabase(QSqlQuery query);
	QList<CharacteristicTypeContext*> ReadCharacteristicTypesFromDatabase();
	QList<BindingContext*> ReadBindingsFromDatabase(QString majorTableName, int fk);
	QList<ParameterTableContext*> ReadParametersFromDatabase(QString majorTableName, QString minorTableName, int fk);

	void TransformQueryToEquipments(QSqlQuery query, QList<EquipmentContext*>& equipments);

private:
	DbReader() {};
	DbReader(const DbReader&) {}
};
