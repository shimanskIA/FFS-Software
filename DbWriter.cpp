#include "DbWriter.h"
#include "FFSDatabaseInterfaceFormController.h"

DbWriter& DbWriter::GetDbWriterInstance()
{
	static DbWriter* dbWriterInstance = 0;

	if (dbWriterInstance == 0)
	{
		dbWriterInstance = new DbWriter();
	}

	return *dbWriterInstance;
}

bool DbWriter::WriteToDatabase(QString sqlRequest, QString tableName)
{
	QString idSet = "SET IDENTITY_INSERT %1 ON";
	QSqlQuery query(idSet.arg(tableName));
	return query.exec(sqlRequest);
}

bool DbWriter::AddToDatabase(DbContext* dbContext)
{
	bool wasAnySampleAdded = AddSamples(dbContext->GetSamples());
	bool wasAnyCharacteristicTypeAdded = AddCharacteristicTypes(dbContext->GetCharacteristicTypes());
	bool wasAnyRowBindedOnEquipmentAdded = AddEquipment(dbContext->GetEquipments());
	bool wasAnyRowBindedOnMeasuringSystemAdded = AddMeasuringSystem(dbContext->GetMeasuringSystem());
	return
		wasAnySampleAdded ||
		wasAnyCharacteristicTypeAdded ||
		wasAnyRowBindedOnEquipmentAdded ||
		wasAnyRowBindedOnMeasuringSystemAdded;
}

bool DbWriter::AddSamples(QList<SampleContext*> samples)
{
	bool wasAnySampleAdded = false;
	
	foreach(SampleContext * sample, samples)
	{
		bool wasSingleSampleAdded = AddSample(sample, true);
		wasAnySampleAdded == wasAnySampleAdded || wasSingleSampleAdded;
	}

	return wasAnySampleAdded;
}

bool DbWriter::AddCharacteristicTypes(QList<CharacteristicTypeContext*> characteristicTypes)
{
	bool wasAnyCharacteristicAdded = false;

	foreach(CharacteristicTypeContext * characteristicType, characteristicTypes)
	{
		bool wasSingleCharacteristicAdded = AddCharacteristicType(characteristicType, true);
		wasAnyCharacteristicAdded == wasAnyCharacteristicAdded || wasSingleCharacteristicAdded;
	}

	return wasAnyCharacteristicAdded;
}

bool DbWriter::AddMeasurements(QList<MeasurementContext*> measurements)
{
	bool wasAnyMeasurementAdded = false;
	bool wasAnyMeasurementParameterAdded = false;
	bool wasAnyCharacteristicAdded = false;
	
	foreach(MeasurementContext * measurement, measurements)
	{
		QString sqlReadRequest = "SELECT * FROM measurements WHERE name = '%1' AND date = '%2' AND file_link = '%3' AND repeat_count = %4 AND kinetics_count = %5 AND number_of_channels = %6 AND number_positions = %7 AND fk_sample = %8 AND fk_measuring_system = %9";
		QString name = measurement->GetName();
		QString date = measurement->GetDateTime();
		QString file_link = measurement->GetFileLink();
		uint repeat_count = measurement->GetRepeatCount();
		uint kinetics_count = measurement->GetKineticsCount();
		uint number_of_channels = measurement->GetKineticsCount();
		uint number_positions = measurement->GetNumberPositions();
		int fk_sample = measurement->GetFKSample();
		int fk_measuring_system = measurement->GetFKMeasuringSystem();
		QSqlQuery query = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlReadRequest
			.arg(name)
			.arg(date)
			.arg(file_link)
			.arg(repeat_count)
			.arg(kinetics_count)
			.arg(number_of_channels)
			.arg(number_positions)
			.arg(fk_sample)
			.arg(fk_measuring_system));

		if (query.next())
		{
			bool hasEqual = false;
			int twinId = 0;
			query.previous();

			while (query.next())
			{
				int id = query.value(0).toInt();
				QString sqlParametersReadRequest = "SELECT * FROM measurement_parameters WHERE fk_measurement = %1";
				QString sqlCharacteristicsReadRequest = "SELECT * FROM characteristics WHERE fk_measurement = %1";
				QSqlQuery parametersQuery = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlParametersReadRequest.arg(id));
				QSqlQuery characteristicsQuery = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlCharacteristicsReadRequest.arg(id));

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
					characteristic->SetChannel(characteristicsQuery.value(2).toString().trimmed());
					characteristic->SetNumberOfPoints(characteristicsQuery.value(3).toUInt());
					characteristic->SetBinTime(characteristicsQuery.value(4).toDouble());
					characteristic->SetX(characteristicsQuery.value(5).toString().trimmed());
					characteristic->SetY(characteristicsQuery.value(6).toString().trimmed());
					characteristic->SetWeight(characteristicsQuery.value(7).toDouble());
					characteristic->SetFKCharacteristicType(new CharacteristicTypeContext(characteristicsQuery.value(9).toUInt()));

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
					QList<int>::iterator itCharacteristics = equalCharacteristicsIds.begin();

					foreach(MeasurementParameterContext * measurementParameter, measurement->GetMeasurementParameters())
					{
						measurementParameter->SetId(*itParameters);
						itParameters++;
					}

					foreach(CharacteristicsContext * characteristic, measurement->GetCharacteristics())
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
		}

		int id = measurement->GetId();
		QString sqlWriteRequest = "INSERT INTO measurements(id, name, date, file_link, repeat_count, kinetics_count, number_of_channels, number_positions, fk_sample, fk_measuring_system) VALUES (%1, '%2', '%3', '%4', %5, %6, %7, %8, %9, %10)";
		bool wasSingleMeasurementAdded = WriteToDatabase(sqlWriteRequest
			.arg(id)
			.arg(name)
			.arg(date)
			.arg(file_link)
			.arg(repeat_count)
			.arg(kinetics_count)
			.arg(number_of_channels)
			.arg(number_positions)
			.arg(fk_sample)
			.arg(fk_measuring_system), "measurements");
		wasAnyMeasurementAdded = wasAnyMeasurementAdded || wasSingleMeasurementAdded;
		wasAnyMeasurementParameterAdded = AddMeasurementParameters(measurement->GetMeasurementParameters());
		wasAnyCharacteristicAdded = AddCharacteristics(measurement->GetCharacteristics());
	}

	return wasAnyMeasurementAdded || wasAnyCharacteristicAdded || wasAnyMeasurementParameterAdded;
}

bool DbWriter::AddMeasuringSystem(MeasuringSystemContext* measuringSystem)
{
	bool wasMeasuringSystemAdded = false;
	bool wasAnyMeasurementAdded = false;
	bool wasAnyBindingAdded = false;
	bool equalMeasuringSystemExists = false;
	
	QString sqlReadRequest = "SELECT id FROM measuring_systems";
	QSqlQuery query = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlReadRequest);

	if (!wasEquipmentAdded)
	{
		while (query.next())
		{
			QString sqlBindingsReadQuery = "SELECT fk_equipment FROM bindings WHERE fk_measuring_system = %1";
			int id = query.value(0).toInt();
			QSqlQuery bindingsQuery = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlBindingsReadQuery.arg(id));
			QList<int> equipmentIds;
			bool areEqual = true;

			while (bindingsQuery.next())
			{
				equipmentIds.append(bindingsQuery.value(0).toInt());
			}

			if (equipmentIds.length() == measuringSystem->GetAmountOfBindings())
			{

				foreach(int equipmentId, equipmentIds)
				{
					if (!measuringSystem->ContainsBindingWithThisEquipment(equipmentId))
					{
						areEqual = false;
						break;
					}
				}
			}
			else
			{
				areEqual = false;
			}

			if (areEqual)
			{
				measuringSystem->SetId(id);
				equalMeasuringSystemExists = true;
				break;
			}
		}
	}

	if (!equalMeasuringSystemExists)
	{
		FFSDatabaseInterfaceFormController::ManageCreateMeasuringSystemInputFormRequest();
		measuringSystem->SetName(inputMeasuringSystemCredentials["name"]);
		QString description = inputMeasuringSystemCredentials["description"];

		if (description != "")
		{
			measuringSystem->SetDescription(description);
		}

		measuringSystem->SetMainContributorName(inputMeasuringSystemCredentials["contributor"]);
	}

	QString sqlWriteRequest = "INSERT INTO measuring_systems(id, name, description, main_contributor_name) VALUES (%1, '%2', '%3', '%4')";
	int id = measuringSystem->GetId();
	QString name = measuringSystem->GetName();
	QString description = measuringSystem->GetDescription();
	QString mainContributorName = measuringSystem->GetMainContributorName();
	wasMeasuringSystemAdded = WriteToDatabase(sqlWriteRequest.arg(id).arg(name).arg(description).arg(mainContributorName), "measuring_systems");
	wasAnyBindingAdded = AddBindings(measuringSystem->GetBindings());
	wasAnyMeasurementAdded = AddMeasurements(measuringSystem->GetMeasurements());
	wasEquipmentAdded = false;
	return wasMeasuringSystemAdded || wasAnyBindingAdded || wasAnyMeasurementAdded;
}

bool DbWriter::AddForwardMeasuringSystem(MeasuringSystemContext* measuringSystem)
{
	QString sqlReadRequest = "SELECT * FROM measuring_systems WHERE name = '%1' AND main_contributor_name = '%2'";
	QSqlQuery query = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlReadRequest
		.arg(measuringSystem->GetName())
		.arg(measuringSystem->GetMainContributorName()));

	if (!query.next())
	{
		QString sqlWriteRequest = "INSERT INTO measuring_systems(id, name, description, main_contributor_name) VALUES (%1, '%2', '%3', '%4')";
		int id = measuringSystem->GetId();
		QString name = measuringSystem->GetName();
		QString description = measuringSystem->GetDescription();

		if (description == "")
		{
			description = "Write your description here.";
		}

		QString mainContributorName = measuringSystem->GetMainContributorName();
		bool isRowAdded;
		isRowAdded = WriteToDatabase(sqlWriteRequest.arg(id).arg(name).arg(description).arg(mainContributorName), "measuring_systems");

		if (isRowAdded)
		{
			AddBindings(measuringSystem->GetBindings());
			return true;
		}
	}

	return false;
}

bool DbWriter::AddEquipment(QList<EquipmentContext*> equipments)
{
	bool wasAnyEquipmentParameterAdded = true;
	
	foreach(EquipmentContext * equipment, equipments)
	{
		QString sqlReadRequest = "SELECT * FROM equipments WHERE name = '%1' AND description = '%2'";
		QString name = equipment->GetName();
		QString description = equipment->GetDescription();
		QSqlQuery query = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlReadRequest.arg(name).arg(description));

		if (query.next())
		{
			bool hasEqual = false;
			int twinId = 0;
			query.previous();

			while (query.next())
			{
				int id = query.value(0).toInt();
				QString sqlParametersReadRequest = "SELECT * FROM equipment_parameters WHERE fk_equipment = %1";
				QSqlQuery parametersQuery = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlParametersReadRequest.arg(id));

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
		}

		int id = equipment->GetId();
		QString sqlWriteRequest = "INSERT INTO equipments(id, name, description) VALUES (%1, '%2', '%3')";

		if (WriteToDatabase(sqlWriteRequest.arg(id).arg(name).arg(description), "equipments"))
		{
			wasEquipmentAdded = true;
		}

		wasAnyEquipmentParameterAdded = AddEquipmentParameters(equipment->GetEquipmentParameters());
	}

	return wasEquipmentAdded || wasAnyEquipmentParameterAdded;
}

bool DbWriter::AddMeasurementParameters(QList<MeasurementParameterContext*> measurementParameters)
{
	bool wasAnyMeasurementParameterAdded = false;
	
	foreach(MeasurementParameterContext * measurementParameter, measurementParameters)
	{
		bool wasSingleMeasurementParameterAdded = AddMeasurementParameter(measurementParameter);
		wasAnyMeasurementParameterAdded = wasAnyMeasurementParameterAdded || wasSingleMeasurementParameterAdded;
	}

	return wasAnyMeasurementParameterAdded;
}

bool DbWriter::AddEquipmentParameters(QList<EquipmentParameterContext*> equipmentParameters)
{
	bool wasAnyEquipmentParameterAdded = false;
	
	foreach(EquipmentParameterContext * equipmentParameter, equipmentParameters)
	{
		bool wasSingleEquipmentParameterAdded = AddEquipmentParameter(equipmentParameter);
		wasAnyEquipmentParameterAdded = wasAnyEquipmentParameterAdded || wasSingleEquipmentParameterAdded;
	}

	return wasAnyEquipmentParameterAdded;
}

bool DbWriter::AddCharacteristics(QList<CharacteristicsContext*> characteristics)
{
	bool wasAnyCharacteristicAdded = false;
	
	foreach(CharacteristicsContext * characteristic, characteristics)
	{
		bool wasSingleCharacteristicAdded = AddCharacteristic(characteristic);
		wasAnyCharacteristicAdded = wasAnyCharacteristicAdded || wasSingleCharacteristicAdded;
	}

	return wasAnyCharacteristicAdded;
}

bool DbWriter::AddBindings(QList<BindingContext*> bindings)
{
	bool wasAnyBindingAdded = false;
	
	foreach(BindingContext * binding, bindings)
	{
		QString sqlReadRequest = "SELECT * FROM bindings WHERE fk_measuring_system = %1 AND fk_equipment = %2";
		int fk_equipment = binding->GetFKEquipment();
		int fk_measurement = binding->GetFKMeasuringSystem();
		QSqlQuery query = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlReadRequest.arg(fk_measurement).arg(fk_equipment));

		if (!query.next())
		{
			QString sqlWriteRequest = "INSERT INTO bindings(fk_measuring_system, fk_equipment) VALUES (%1, %2)";
			bool wasSingleBindingAdded = WriteToDatabase(sqlWriteRequest.arg(fk_measurement).arg(fk_equipment), "bindings");
			wasAnyBindingAdded = wasAnyBindingAdded || wasSingleBindingAdded;
		}
	}

	return wasAnyBindingAdded;
}

bool DbWriter::AddBinding(BindingContext* binding)
{
	int fk_equipment = binding->GetFKEquipment();
	int fk_measurement = binding->GetFKMeasuringSystem();
	QString sqlWriteRequest = "INSERT INTO bindings(fk_measuring_system, fk_equipment) VALUES (%1, %2)";
	return WriteToDatabase(sqlWriteRequest.arg(fk_measurement).arg(fk_equipment), "bindings");
}

bool DbWriter::AddEquipmentItem(EquipmentContext* equipmentItem)
{
	int id = equipmentItem->GetId();
	QString name = equipmentItem->GetName();
	QString description = equipmentItem->GetDescription();
	QString sqlWriteRequest = "INSERT INTO equipments(id, name, description) VALUES (%1, '%2', '%3')";
	bool isRowAdded;
	isRowAdded = WriteToDatabase(sqlWriteRequest.arg(id).arg(name).arg(description), "equipments");

	if (isRowAdded)
	{
		BindingContext* binding = equipmentItem->GetBinding();

		if (binding != nullptr)
		{
			AddBinding(binding);
		}
	}

	return isRowAdded;
}

bool DbWriter::AddSample(SampleContext* sample, bool isComplex)
{
	QString sqlReadRequest = "SELECT * FROM samples WHERE name = '%1' AND description = '%2'";
	int id = sample->GetId();
	QString name = sample->GetName();
	QString description = sample->GetDescription();
	QSqlQuery query = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlReadRequest.arg(name).arg(description));

	if (!query.next())
	{
		QString sqlWriteRequest = "INSERT INTO samples(id, name, description) VALUES (%1, '%2', '%3')";
		return WriteToDatabase(sqlWriteRequest.arg(id).arg(name).arg(description), "samples");
	}
		
	if (isComplex)
	{
		sample->SetId(query.value(0).toInt());
	}

	return false;
}

bool DbWriter::AddCharacteristicType(CharacteristicTypeContext* characteristicType, bool isComplex)
{
	QString sqlReadRequest = "SELECT * FROM characteristic_types WHERE name = '%1'";
	int id = characteristicType->GetId();
	QString name = characteristicType->GetName();
	QString description = characteristicType->GetDescription();
	QSqlQuery query = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlReadRequest.arg(name));

	if (!query.next())
	{
		QString sqlWriteRequest = "INSERT INTO characteristic_types(id, name, description) VALUES (%1, '%2', '%3')";
		return WriteToDatabase(sqlWriteRequest.arg(id).arg(name).arg(description), "characteristic_types");
	}

	if (isComplex)
	{
		characteristicType->SetId(query.value(0).toInt());
	}

	return false;
}

bool DbWriter::AddCharacteristic(CharacteristicsContext* characteristic)
{
	QString sqlReadRequest = "SELECT * FROM characteristics WHERE channel = '%1' AND number_of_points = %2 AND bin_time = %3 AND x = '%4' AND y = '%5' AND weight = %6 AND fk_measurement = %7 AND fk_characteristic_type = %8";
	int id = characteristic->GetId();
	QString name = characteristic->GetName();
	QString channel = characteristic->GetChannel();
	uint number_of_points = characteristic->GetNumberOfPoints();
	double bin_time = characteristic->GetBinTime();
	QString x = characteristic->GetX();
	QString y = characteristic->GetY();
	double weight = characteristic->GetWeight();
	int fk_measurement = characteristic->GetFKMeasurement();
	int fk_characteristic_type = characteristic->GetFKCharacteristicType();
	QSqlQuery query = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlReadRequest
		.arg(channel)
		.arg(number_of_points)
		.arg(bin_time)
		.arg(x)
		.arg(y)
		.arg(weight)
		.arg(fk_measurement)
		.arg(fk_characteristic_type));

	if (!query.next())
	{
		QString sqlWriteRequest = "INSERT INTO characteristics(id, name, channel, number_of_points, bin_time, x, y, weight, fk_measurement, fk_characteristic_type) VALUES (%1, '%2', '%3', %4, %5, '%6', '%7', %8, %9, %10)";
		return WriteToDatabase(sqlWriteRequest
			.arg(id)
			.arg(name)
			.arg(channel)
			.arg(number_of_points)
			.arg(bin_time)
			.arg(x)
			.arg(y)
			.arg(weight)
			.arg(fk_measurement)
			.arg(fk_characteristic_type), "characteristics");
	}

	return false;
}

bool DbWriter::AddMeasurement(MeasurementContext* measurement)
{
	int id = measurement->GetId();
	QString name = measurement->GetName();
	QString date = measurement->GetDateTime();
	QString file_link = measurement->GetFileLink();
	uint repeat_count = measurement->GetRepeatCount();
	uint kinetics_count = measurement->GetKineticsCount();
	uint number_of_channels = measurement->GetKineticsCount();
	uint number_positions = measurement->GetNumberPositions();
	int fk_sample = measurement->GetFKSample();
	int fk_measuring_system = measurement->GetFKMeasuringSystem();
	QString sqlWriteRequest = "INSERT INTO measurements(id, name, date, file_link, repeat_count, kinetics_count, number_of_channels, number_positions, fk_sample, fk_measuring_system) VALUES (%1, '%2', '%3', '%4', %5, %6, %7, %8, %9, %10)";
	return WriteToDatabase(sqlWriteRequest
		.arg(id)
		.arg(name)
		.arg(date)
		.arg(file_link)
		.arg(repeat_count)
		.arg(kinetics_count)
		.arg(number_of_channels)
		.arg(number_positions)
		.arg(fk_sample)
		.arg(fk_measuring_system), "measurements");
}

bool DbWriter::AddEquipmentParameter(EquipmentParameterContext* equipmentParameter)
{
	QString sqlReadRequest = "SELECT * FROM equipment_parameters WHERE name = '%1' AND fk_equipment = %2";
	int id = equipmentParameter->GetId();
	QString name = equipmentParameter->GetName();
	QString value = equipmentParameter->GetValue();
	int fk_equipment = equipmentParameter->GetFKEquipment();
	QSqlQuery query = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlReadRequest.arg(name).arg(fk_equipment));

	if (!query.next())
	{
		QString sqlWriteRequest = "INSERT INTO equipment_parameters(id, name, value, fk_equipment) VALUES (%1, '%2', '%3', %4)";
		return WriteToDatabase(sqlWriteRequest.arg(id).arg(name).arg(value).arg(fk_equipment), "equipment_parameters");
	}

	return false;
}

bool DbWriter::AddMeasurementParameter(MeasurementParameterContext* measurementParameter)
{
	QString sqlReadRequest = "SELECT * FROM measurement_parameters WHERE name = '%1' AND fk_measurement = %2";
	int id = measurementParameter->GetId();
	QString name = measurementParameter->GetName();
	QString value = measurementParameter->GetValue();
	int fk_measurement = measurementParameter->GetFKMeasurement();
	QSqlQuery query = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlReadRequest.arg(name).arg(fk_measurement));

	if (!query.next())
	{
		QString sqlWriteRequest = "INSERT INTO measurement_parameters(id, name, value, fk_measurement) VALUES (%1, '%2', '%3', %4)";
		return WriteToDatabase(sqlWriteRequest.arg(id).arg(name).arg(value).arg(fk_measurement), "measurement_parameters");
	}

	return false;
}

bool DbWriter::AddRow(QVariant tableContext)
{
	if (tableContext.canConvert<EquipmentContext*>())
	{
		return AddEquipmentItem(tableContext.value<EquipmentContext*>());
	}
	else if (tableContext.canConvert<SampleContext*>())
	{
		return AddSample(tableContext.value<SampleContext*>());
	}
	else if (tableContext.canConvert<CharacteristicTypeContext*>())
	{
		return AddCharacteristicType(tableContext.value<CharacteristicTypeContext*>());
	}
	else if (tableContext.canConvert<MeasurementContext*>())
	{
		return AddMeasurement(tableContext.value<MeasurementContext*>());
	}
	else if (tableContext.canConvert<CharacteristicsContext*>())
	{
		return AddCharacteristic(tableContext.value<CharacteristicsContext*>());
	}
	else if (tableContext.canConvert<EquipmentParameterContext*>())
	{
		return AddEquipmentParameter(tableContext.value<EquipmentParameterContext*>());
	}
	else if (tableContext.canConvert<MeasurementParameterContext*>())
	{
		return AddMeasurementParameter(tableContext.value<MeasurementParameterContext*>());
	}
	else if (tableContext.canConvert<MeasuringSystemContext*>())
	{
		return AddForwardMeasuringSystem(tableContext.value<MeasuringSystemContext*>());
	}

	return false;
}

void DbWriter::SetInputMeasuringSystemCredentials(QMap<QString, QString> credentials)
{
	this->inputMeasuringSystemCredentials = credentials;
}

Q_DECLARE_METATYPE(EquipmentContext*);
Q_DECLARE_METATYPE(SampleContext*);
Q_DECLARE_METATYPE(CharacteristicTypeContext*);
Q_DECLARE_METATYPE(MeasurementContext*);
Q_DECLARE_METATYPE(CharacteristicsContext*);
Q_DECLARE_METATYPE(EquipmentParameterContext*);
Q_DECLARE_METATYPE(MeasurementParameterContext*);
Q_DECLARE_METATYPE(MeasuringSystemContext*);