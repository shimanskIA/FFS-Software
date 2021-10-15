#include "DbConnection.h"

DbConnection::DbConnection()
{
	database = QSqlDatabase::addDatabase("QODBC");
	database.setDatabaseName("DRIVER={SQL SERVER};SERVER=ACER-A515\\SQLEXPRESS;DATABASE=ffsdbv3;UID=Ivan;PWD=;Trusted_Connection=Yes;");
	
	if (!database.open())
	{
		qWarning("Unable to connect to database.");
	}
}

DbConnection& DbConnection::GetDbConnectionInstance()
{
	static DbConnection* dbConnectionInstance = 0;

	if (dbConnectionInstance == 0)
	{
		dbConnectionInstance = new DbConnection();
	}

	return *dbConnectionInstance;
}

void DbConnection::WriteToDatabase(QString sqlRequest, QString tableName)
{
	QString idSet = "SET IDENTITY_INSERT %1 ON";
	QSqlQuery query(idSet.arg(tableName));
	query.exec(sqlRequest);
}

QSqlQuery DbConnection::ReadFromDatabase(QString sqlRequest)
{
	QSqlQuery query;

	if (!query.exec(sqlRequest))
	{
		qWarning("Database request wasn't proceeded.");
	}

	return query;
}

void DbConnection::AddToDatabase(DbContext* dbContext)
{
	AddSamples(dbContext->GetSamples());
	AddCharacteristicTypes(dbContext->GetCharacteristicTypes());
	AddMeasurements(dbContext->GetMeasurements(), dbContext);
}

void DbConnection::AddSamples(QList<SampleContext*> samples)
{
	foreach(SampleContext* sample, samples)
	{
		QString sqlReadRequest = "SELECT * FROM samples WHERE name = '%1' AND description = '%2'";
		QString name = sample->GetName();
		QString description = sample->GetDescription();
		QSqlQuery query = ReadFromDatabase(sqlReadRequest.arg(name).arg(description));

		if (!query.next())
		{
			int id = sample->GetId();
			QString sqlWriteRequest = "INSERT INTO samples(id, name, description) VALUES (%1, '%2', '%3')";
			WriteToDatabase(sqlWriteRequest.arg(id).arg(name).arg(description), "samples");
		}
		else
		{
			sample->SetId(query.value(0).toInt());
		}
	}
}

void DbConnection::AddCharacteristicTypes(QList<CharacteristicTypeContext*> characteristic_types)
{
	foreach(CharacteristicTypeContext* characteristic_type, characteristic_types)
	{
		QString sqlReadRequest = "SELECT * FROM characteristic_types WHERE name = '%1' AND description = '%2'";
		QString name = characteristic_type->GetName();
		QString description = characteristic_type->GetDescription();
		QSqlQuery query = ReadFromDatabase(sqlReadRequest.arg(name).arg(description));

		if (!query.next())
		{
			int id = characteristic_type->GetId();
			QString sqlWriteRequest = "INSERT INTO characteristic_types(id, name, description) VALUES (%1, '%2', '%3')";
			WriteToDatabase(sqlWriteRequest.arg(id).arg(name).arg(description), "characteristic_types");
		}
		else
		{
			characteristic_type->SetId(query.value(0).toInt());
		}
	}
}

void DbConnection::AddMeasurements(QList<MeasurementContext*> measurements, DbContext* dbContext)
{
	foreach(MeasurementContext* measurement, measurements)
	{
		QString sqlReadRequest = "SELECT * FROM measurements WHERE name = '%1' AND date = '%2' AND file_link = '%3' AND repeat_count = %4 AND kinetics_count = %5 AND number_of_channels = %6 AND number_positions = %7 AND fk_sample = %8";
		QString name = measurement->GetName();
		QString date = measurement->GetDateTime();
		QString file_link = measurement->GetFileLink();
		int repeat_count = measurement->GetRepeatCount();
		int kinetics_count = measurement->GetKineticsCount();
		int number_of_channels = measurement->GetKineticsCount();
		int number_positions = measurement->GetNumberPositions();
		int fk_sample = measurement->GetFKSample();
		QSqlQuery query = ReadFromDatabase(sqlReadRequest
			.arg(name)
			.arg(date)
			.arg(file_link)
			.arg(repeat_count)
			.arg(kinetics_count)
			.arg(number_of_channels)
			.arg(number_positions)
			.arg(fk_sample));

		if (!query.next())
		{
			int id = measurement->GetId();
			QString sqlWriteRequest = "INSERT INTO measurements(id, name, date, file_link, repeat_count, kinetics_count, number_of_channels, number_positions, fk_sample) VALUES (%1, '%2', '%3', '%4', %5, %6, %7, %8, %9)";
			WriteToDatabase(sqlWriteRequest
				.arg(id)
				.arg(name)
				.arg(date)
				.arg(file_link)
				.arg(repeat_count)
				.arg(kinetics_count)
				.arg(number_of_channels)
				.arg(number_positions)
				.arg(fk_sample), "characteristic_types");
			AddMeasurementParameters(dbContext->GetMeasurementParameters());
			AddCharacteristics(dbContext->GetCharacteristics());
		}
		else
		{
			bool hasEqual = false;
			int twinId = 0;
			query.previous();

			while (query.next()) 
			{
				int id = query.value(0).toInt();
				QString sqlParametersReadRequest = "SELECT * FROM measurement_parameters WHERE fk_measurement = %1";
				QString sqlCharacteristicsReadRequest = "SELECT * FROM characteristics WHERE fk_measurement = %1";
				QSqlQuery parametersQuery = ReadFromDatabase(sqlParametersReadRequest.arg(id));
				QSqlQuery characteristicsQuery = ReadFromDatabase(sqlCharacteristicsReadRequest.arg(id));

				QList<MeasurementParameterContext*> measurementParameters = dbContext->GetMeasurementParameters();
				QList<CharacteristicsContext*> characteristics = dbContext->GetCharacteristics();
				QList<int> equalParametersIds;
				QList<int> equalCharacteristicsIds;

				while (parametersQuery.next())
				{
					QString parameterName = parametersQuery.value(1).toString().trimmed();
					QString parameterValue = parametersQuery.value(2).toString().trimmed();

					foreach(MeasurementParameterContext * measurementParameter, measurementParameters)
					{
						if (parameterName == measurementParameter->GetName() && parameterValue == measurementParameter->GetValue())
						{
							int parameterId = parametersQuery.value(0).toInt();
							equalParametersIds.append(parameterId);
							break;
						}
					}
				}

				if (equalParametersIds.length() < measurementParameters.length())
				{
					continue;
				}

				while (characteristicsQuery.next())
				{
					QString channel = characteristicsQuery.value(1).toString().trimmed();
					int numberOfPoints = characteristicsQuery.value(2).toInt();
					double binTime = characteristicsQuery.value(3).toDouble();
					QString x = characteristicsQuery.value(4).toString().trimmed();
					QString y = characteristicsQuery.value(5).toString().trimmed();
					double weight = characteristicsQuery.value(6).toDouble();
					int fk_characteristic_type = characteristicsQuery.value(8).toInt();

					foreach(CharacteristicsContext * characteristic, characteristics)
					{
						if (channel == characteristic->GetChannel() && 
							numberOfPoints == characteristic->GetNumberOfPoints() &&
							qFabs(binTime - characteristic->GetBinTime()) < 1e-05 &&
							x == characteristic->GetX().trimmed() &&
							y == characteristic->GetY().trimmed() &&
							qFabs(weight - characteristic->GetWeight()) < 1e-05 &&
							fk_characteristic_type == characteristic->GetFKCharacteristicType())
						{
							int characteristicId = characteristicsQuery.value(0).toInt();
							equalCharacteristicsIds.append(characteristicId);
							break;
						}
					}
				}

				if (equalCharacteristicsIds.length() == characteristics.length())
				{
					hasEqual = true;
					twinId = id;
					QList<int>::iterator itParameters = equalParametersIds.begin();
					QList<int>::iterator itCharacteristics = equalParametersIds.begin();

					foreach(MeasurementParameterContext * measurementParameter, measurementParameters)
					{
						measurementParameter->SetId(*itParameters);
						itParameters++;
					}

					foreach(CharacteristicsContext* characteristic, characteristics)
					{
						characteristic->SetId(*itCharacteristics);
						itCharacteristics++;
					}

					break;
				}
			}

			if (hasEqual)
			{
				measurement->SetId(twinId);
			}
			else
			{
				int id = measurement->GetId();
				QString sqlWriteRequest = "INSERT INTO measurements(id, name, date, file_link, repeat_count, kinetics_count, number_of_channels, number_positions, fk_sample) VALUES (%1, '%2', '%3', '%4', %5, %6, %7, %8, %9)";
				WriteToDatabase(sqlWriteRequest
					.arg(id)
					.arg(name)
					.arg(date)
					.arg(file_link)
					.arg(repeat_count)
					.arg(kinetics_count)
					.arg(number_of_channels)
					.arg(number_positions)
					.arg(fk_sample), "characteristic_types");
				AddMeasurementParameters(dbContext->GetMeasurementParameters());
				AddCharacteristics(dbContext->GetCharacteristics());
			}
		}
	}
}

void DbConnection::AddMeasurementParameters(QList<MeasurementParameterContext*> measurementParameters)
{
	foreach(MeasurementParameterContext * measurementParameter, measurementParameters)
	{
		QString sqlWriteRequest = "INSERT INTO measurement_parameters(id, name, value, fk_measurement) VALUES (%1, '%2', '%3', %4)";
		int id = measurementParameter->GetId();
		QString name = measurementParameter->GetName();
		QString value = measurementParameter->GetValue();
		int fk_measurement = measurementParameter->GetFKMeasurement();
		WriteToDatabase(sqlWriteRequest.arg(id).arg(name).arg(value).arg(fk_measurement), "measurement_parameters");
	}
}

void DbConnection::AddCharacteristics(QList<CharacteristicsContext*> characteristics)
{
	foreach(CharacteristicsContext* characteristic, characteristics)
	{
		QString sqlWriteRequest = "INSERT INTO characteristics(id, channel, number_of_points, bin_time, x, y, weight, fk_measurement, fk_characteristic_type) VALUES (%1, '%2', %3, %4, '%5', '%6', %7, %8, %9)";
		int id = characteristic->GetId();
		QString channel = characteristic->GetChannel();
		int number_of_points = characteristic->GetNumberOfPoints();
		double bin_time = characteristic->GetBinTime();
		QString x = characteristic->GetX();
		QString y = characteristic->GetY();
		double weight = characteristic->GetWeight();
		int fk_measurement = characteristic->GetFKMeasurement();
		int fk_characteristic_type = characteristic->GetFKCharacteristicType();
		WriteToDatabase(sqlWriteRequest
			.arg(id).arg(channel)
			.arg(number_of_points)
			.arg(bin_time)
			.arg(x)
			.arg(y)
			.arg(weight)
			.arg(fk_measurement)
			.arg(fk_characteristic_type), "characteristics");
	}
}

