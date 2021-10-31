#include "DbReader.h"

DbReader::DbReader()
{

}

QSqlQuery DbReader::ReadFromDatabase(QString sqlRequest)
{
	QSqlQuery query;

	if (!query.exec(sqlRequest))
	{
		qWarning("Database read request wasn't proceeded.");
	}

	return query;
}

bool DbReader::ReadAbscissaFromDatabase(int characteristicId, QVector<double>& x)
{
	QString sqlReadRequest = "SELECT x FROM characteristics WHERE id = %1";
	QSqlQuery query = ReadFromDatabase(sqlReadRequest.arg(characteristicId));
	query.next();
	QString rawX = query.value(0).toString().trimmed();
	QStringList separatedX = rawX.split(' ');

	foreach(QString xValue, separatedX)
	{
		bool wasConverted;
		double realValue = xValue.toDouble(&wasConverted);

		if (!wasConverted)
		{
			return false;
		}

		x.append(realValue);
	}

	return true;
}

bool DbReader::ReadOrdinateFromDatabase(int characteristicId, QVector<double>& y)
{
	QString sqlReadRequest = "SELECT y FROM characteristics WHERE id = %1";
	QSqlQuery query = ReadFromDatabase(sqlReadRequest.arg(characteristicId));
	query.next();
	QString rawY = query.value(0).toString().trimmed();
	QStringList separatedY = rawY.split(' ');

	foreach(QString yValue, separatedY)
	{
		bool wasConverted;
		double realValue = yValue.toDouble(&wasConverted);

		if (!wasConverted)
		{
			return false;
		}

		y.append(realValue);
	}

	return true;
}

QList<MeasuringSystemContext*> DbReader::ReadMeasuringSystemsFromDatabase()
{
	QString sqlReadRequest = "SELECT * FROM measuring_systems";
	QSqlQuery query = ReadFromDatabase(sqlReadRequest);
	QList<MeasuringSystemContext*> measuringSystems;

	while (query.next())
	{
		int id = query.value(0).toInt();
		MeasuringSystemContext* measuringSystem = new MeasuringSystemContext(id);
		measuringSystem->SetName(query.value(1).toString().trimmed());
		measuringSystem->SetDescription(query.value(2).toString().trimmed());
		measuringSystem->SetMainContributorName(query.value(3).toString().trimmed());
		measuringSystems.append(measuringSystem);
	}

	return measuringSystems;

}

QList<MeasurementContext*> DbReader::ReadMeasurementsFromDatabase()
{
	QString sqlReadRequest = "SELECT * FROM measurements";
	QSqlQuery query = ReadFromDatabase(sqlReadRequest);
	QList<MeasurementContext*> measurements;

	while (query.next())
	{
		int id = query.value(0).toInt();
		MeasurementContext* measurement = new MeasurementContext(id);
		measurement->SetName(query.value(1).toString().trimmed());
		measurement->SetDateTime(query.value(2).toString().trimmed());
		measurement->SetFileLink(query.value(3).toString().trimmed());
		measurement->SetRepeatCount(query.value(4).toInt());
		measurement->SetKineticsCount(query.value(5).toInt());
		measurement->SetNumberOfChannels(query.value(6).toInt());
		measurement->SetNumberPositions(query.value(7).toInt());

		int fk_sample = query.value(8).toInt();
		SampleContext* sample = new SampleContext(fk_sample);
		QString sqlSampleReadRequest = "SELECT * FROM samples WHERE id = %1";
		QSqlQuery sampleQuery = ReadFromDatabase(sqlSampleReadRequest.arg(fk_sample));
		if (sampleQuery.next())
		{
			sample->SetName(sampleQuery.value(1).toString().trimmed());
			measurement->SetFKSample(sample);
		}

		measurements.append(measurement);
	}

	return measurements;
}

QList<MeasurementContext*> DbReader::ReadMeasurementsFromDatabase(QString majorTableName, int fk)
{
	QString sqlReadRequest = "SELECT * FROM measurements WHERE fk_%1 = %2";
	QSqlQuery query = ReadFromDatabase(sqlReadRequest.arg(majorTableName).arg(fk));
	QList<MeasurementContext*> measurements;

	while (query.next())
	{
		int id = query.value(0).toInt();
		MeasurementContext* measurement = new MeasurementContext(id);
		measurement->SetName(query.value(1).toString().trimmed());
		measurement->SetDateTime(query.value(2).toString().trimmed());
		measurement->SetFileLink(query.value(3).toString().trimmed());
		measurement->SetRepeatCount(query.value(4).toInt());
		measurement->SetKineticsCount(query.value(5).toInt());
		measurement->SetNumberOfChannels(query.value(6).toInt());
		measurement->SetNumberPositions(query.value(7).toInt());
		measurements.append(measurement);
	}

	return measurements;
}

QList<SampleContext*> DbReader::ReadSamplesFromDatabase()
{
	QString sqlReadRequest = "SELECT * FROM samples";
	QSqlQuery query = ReadFromDatabase(sqlReadRequest);
	QList<SampleContext*> samples;

	while (query.next())
	{
		int id = query.value(0).toInt();
		SampleContext* sample = new SampleContext(id);
		sample->SetName(query.value(1).toString().trimmed());
		sample->SetDescription(query.value(2).toString().trimmed());
		samples.append(sample);
	}

	return samples;
}

QList<EquipmentContext*> DbReader::ReadEquipmentsFromDatabase()
{
	QString sqlReadRequest = "SELECT * FROM equipments";
	QSqlQuery query = ReadFromDatabase(sqlReadRequest);
	QList<EquipmentContext*> equipments;

	while (query.next())
	{
		int id = query.value(0).toInt();
		EquipmentContext* equipment = new EquipmentContext(id);
		equipment->SetName(query.value(1).toString().trimmed());
		equipment->SetDescription(query.value(2).toString().trimmed());
		equipments.append(equipment);
	}

	return equipments;
}

QList<CharacteristicsContext*> DbReader::ReadCharacteristicsFromDatabase(QString sqlReadRequest)
{
	QSqlQuery query = ReadFromDatabase(sqlReadRequest);
	QList<CharacteristicsContext*> characteristics;

	while (query.next())
	{
		int id = query.value(0).toInt();
		CharacteristicsContext* characteristic = new CharacteristicsContext(id);
		characteristic->SetChannel(query.value(1).toString().trimmed());
		characteristic->SetNumberOfPoints(query.value(2).toInt());
		characteristic->SetBinTime(query.value(3).toDouble());
		characteristic->SetWeight(query.value(6).toDouble());

		int fk_characteristic_type = query.value(8).toInt();
		CharacteristicTypeContext* characteristicType = new CharacteristicTypeContext(fk_characteristic_type);
		QString sqlSampleReadRequest = "SELECT * FROM characteristic_types WHERE id = %1";
		QSqlQuery characteristicTypeQuery = ReadFromDatabase(sqlSampleReadRequest.arg(fk_characteristic_type));
		if (characteristicTypeQuery.next())
		{
			characteristicType->SetName(characteristicTypeQuery.value(1).toString().trimmed());
			characteristic->SetFKCharacteristicType(characteristicType);
		}

		characteristics.append(characteristic);
	}

	return characteristics;
}

QList<CharacteristicTypeContext*> DbReader::ReadCharacteristicTypesFromDatabase()
{
	QString sqlReadRequest = "SELECT * FROM characteristic_types";
	QSqlQuery query = ReadFromDatabase(sqlReadRequest);
	QList<CharacteristicTypeContext*> characteristicTypes;

	while (query.next())
	{
		int id = query.value(0).toInt();
		CharacteristicTypeContext* characteristicType = new CharacteristicTypeContext(id);
		characteristicType->SetName(query.value(1).toString().trimmed());
		characteristicType->SetDescription(query.value(2).toString().trimmed());
		characteristicTypes.append(characteristicType);
	}

	return characteristicTypes;
}

QList<BindingContext*> DbReader::ReadBindingsFromDatabase(QString majorTableName, int fk)
{
	QString sqlReadRequest = "SELECT * FROM bindings WHERE fk_%1 = %2";
	QSqlQuery query = ReadFromDatabase(sqlReadRequest.arg(majorTableName).arg(fk));
	QList<BindingContext*> bindings;

	while (query.next())
	{
		BindingContext* binding = new BindingContext();
		binding->SetFKMeasuringSystem(query.value(0).toInt());
		binding->SetFKEquipment(query.value(1).toInt());
		bindings.append(binding);
	}

	return bindings;
}

QList<ParameterTableContext*> DbReader::ReadParametersFromDatabase(QString majorTableName, QString minorTableName, int fk)
{
	QString sqlReadRequest = "SELECT * FROM %1 WHERE fk_%2 = %3";

	QSqlQuery query = ReadFromDatabase(sqlReadRequest.arg(minorTableName).arg(majorTableName).arg(fk));
	QList<ParameterTableContext*> parameters;

	while (query.next())
	{
		int id = query.value(0).toInt();
		ParameterTableContext* parameter = new ParameterTableContext(id);
		parameter->SetName(query.value(1).toString().trimmed());
		parameter->SetValue(query.value(2).toString().trimmed());
		parameters.append(parameter);
	}

	return parameters;
}