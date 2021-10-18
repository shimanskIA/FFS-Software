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
	AddEquipment(dbContext->GetEquipments(), dbContext);

	AddBindings(dbContext->GetBindings());
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
			AddMeasurementParameters(measurement->GetMeasurementParameters());
			AddCharacteristics(measurement->GetCharacteristics());
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

				QList<int> equalParametersIds;
				QList<int> equalCharacteristicsIds;

				while (parametersQuery.next())
				{
					MeasurementParameterContext* measurementParameter = new MeasurementParameterContext();
					measurementParameter->SetName(parametersQuery.value(1).toString().trimmed());
					measurementParameter->SetValue(parametersQuery.value(2).toString().trimmed());

					if (measurement->ContainsMeasurementParameter(measurementParameter))
					{
						int parameterId = parametersQuery.value(0).toInt();
						equalParametersIds.append(parameterId);
					}
				}

				if (equalParametersIds.length() < measurement->GetAmountOfMeasurementParameters())
				{
					continue;
				}

				while (characteristicsQuery.next())
				{
					CharacteristicsContext* characteristic = new CharacteristicsContext();
					characteristic->SetChannel(characteristicsQuery.value(1).toString().trimmed());
					characteristic->SetNumberOfPoints(characteristicsQuery.value(2).toInt());
					characteristic->SetBinTime(characteristicsQuery.value(3).toDouble());
					characteristic->SetX(characteristicsQuery.value(4).toString().trimmed());
					characteristic->SetY(characteristicsQuery.value(5).toString().trimmed());
					characteristic->SetWeight(characteristicsQuery.value(6).toDouble());
					characteristic->SetFKCharacteristicType(new CharacteristicTypeContext(characteristicsQuery.value(8).toInt()));

					if (measurement->ContainsCharacteristic(characteristic))
					{
						int characteristicId = characteristicsQuery.value(0).toInt();
						equalCharacteristicsIds.append(characteristicId);
					}

				}

				if (equalCharacteristicsIds.length() == measurement->GetAmountOfCharacteristics())
				{
					hasEqual = true;
					twinId = id;
					QList<int>::iterator itParameters = equalParametersIds.begin();
					QList<int>::iterator itCharacteristics = equalParametersIds.begin();

					foreach(MeasurementParameterContext * measurementParameter, measurement->GetMeasurementParameters())
					{
						measurementParameter->SetId(*itParameters);
						itParameters++;
					}

					foreach(CharacteristicsContext* characteristic, measurement->GetCharacteristics())
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
				AddMeasurementParameters(measurement->GetMeasurementParameters());
				AddCharacteristics(measurement->GetCharacteristics());
			}
		}
	}
}

void DbConnection::AddEquipment(QList<EquipmentContext*> equipments, DbContext* dbContext)
{
	foreach(EquipmentContext * equipment, equipments)
	{
		QString sqlReadRequest = "SELECT * FROM equipments WHERE name = '%1' AND description = '%2'";
		QString name = equipment->GetName();
		QString description = equipment->GetDescription();
		QSqlQuery query = ReadFromDatabase(sqlReadRequest.arg(name).arg(description));

		if (!query.next())
		{
			int id = equipment->GetId();
			QString sqlWriteRequest = "INSERT INTO equipments(id, name, description) VALUES (%1, '%2', '%3')";
			WriteToDatabase(sqlWriteRequest.arg(id).arg(name).arg(description), "equipments");
			AddEquipmentParameters(equipment->GetEquipmentParameters());
		}
		else
		{
			bool hasEqual = false;
			int twinId = 0;
			query.previous();

			while (query.next())
			{
				int id = query.value(0).toInt();
				QString sqlParametersReadRequest = "SELECT * FROM equipment_parameters WHERE fk_equipment = %1";
				QSqlQuery parametersQuery = ReadFromDatabase(sqlParametersReadRequest.arg(id));

				QList<int> equalParametersIds;

				while (parametersQuery.next())
				{
					EquipmentParameterContext* equipmentParameter = new EquipmentParameterContext();
					equipmentParameter->SetName(parametersQuery.value(1).toString().trimmed());
					equipmentParameter->SetValue(parametersQuery.value(2).toString().trimmed());

					if (equipment->ContainsEquipmentParameter(equipmentParameter))
					{
						int parameterId = parametersQuery.value(0).toInt();
						equalParametersIds.append(parameterId);
					}
				}

				if (equalParametersIds.length() == equipment->GetAmountOfEquipmentParameters())
				{
					hasEqual = true;
					twinId = id;
					QList<int>::iterator itParameters = equalParametersIds.begin();

					foreach(EquipmentParameterContext * equipmentParameter, equipment->GetEquipmentParameters())
					{
						equipmentParameter->SetId(*itParameters);
						itParameters++;
					}

					break;
				}
			}

			if (hasEqual)
			{
				equipment->SetId(twinId);
			}
			else
			{
				int id = equipment->GetId();
				QString sqlWriteRequest = "INSERT INTO equipments(id, name, description) VALUES (%1, '%2', '%3')";
				WriteToDatabase(sqlWriteRequest.arg(id).arg(name).arg(description), "equipments");
				AddEquipmentParameters(equipment->GetEquipmentParameters());
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

void DbConnection::AddEquipmentParameters(QList<EquipmentParameterContext*> equipmentParameters)
{
	foreach(EquipmentParameterContext * equipmentParameter, equipmentParameters)
	{
		QString sqlWriteRequest = "INSERT INTO equipment_parameters(id, name, value, fk_equipment) VALUES (%1, '%2', '%3', %4)";
		int id = equipmentParameter->GetId();
		QString name = equipmentParameter->GetName();
		QString value = equipmentParameter->GetValue();
		int fk_equipment = equipmentParameter->GetFKEquipment();
		WriteToDatabase(sqlWriteRequest.arg(id).arg(name).arg(value).arg(fk_equipment), "equipment_parameters");
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

void DbConnection::AddBindings(QList<BindingContext*> bindings)
{
	foreach(BindingContext * binding, bindings)
	{
		QString sqlReadRequest = "SELECT * FROM bindings WHERE fk_measurement = %1 AND fk_equipment = %2";
		int fk_equipment = binding->GetFKEquipment();
		int fk_measurement = binding->GetFKMeasurement();
		QSqlQuery query = ReadFromDatabase(sqlReadRequest.arg(fk_measurement).arg(fk_equipment));

		if (!query.next())
		{
			QString sqlWriteRequest = "INSERT INTO bindings(fk_measurement, fk_equipment) VALUES (%1, %2)";
			WriteToDatabase(sqlWriteRequest.arg(fk_measurement).arg(fk_equipment), "bindings");
		}
	}
}

QList<MeasurementContext*> DbConnection::ReadMeasurementsFromDatabase()
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

QList<SampleContext*> DbConnection::ReadSamplesFromDatabase()
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

QList<EquipmentContext*> DbConnection::ReadEquipmentsFromDatabase()
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