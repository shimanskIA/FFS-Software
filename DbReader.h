#pragma once

#include "DbContext.h"
#include "DbConnection.h"

#include <QString>
#include <QtSql>

class DbReader
{
public:
	DbReader();

	QSqlQuery ReadFromDatabase(QString sqlRequest);

	bool ReadAbscissaFromDatabase(int characteristicId, QVector<double>& x);
	bool ReadOrdinateFromDatabase(int characteristicId, QVector<double>& y);

	QList<MeasuringSystemContext*> ReadMeasuringSystemsFromDatabase();
	QList<MeasurementContext*> ReadMeasurementsFromDatabase();
	QList<MeasurementContext*> ReadMeasurementsFromDatabase(QString majortableName, int fk);
	QList<SampleContext*> ReadSamplesFromDatabase();
	QList<EquipmentContext*> ReadEquipmentsFromDatabase();
	QList<EquipmentContext*> ReadExistingEquipmentFromDatabase(int fk_measuring_system);
	QList<CharacteristicsContext*> ReadCharacteristicsFromDatabase(QString sqlReadRequest);
	QList<CharacteristicTypeContext*> ReadCharacteristicTypesFromDatabase();
	QList<BindingContext*> ReadBindingsFromDatabase(QString majorTableName, int fk);
	QList<ParameterTableContext*> ReadParametersFromDatabase(QString majorTableName, QString minorTableName, int fk);
};
