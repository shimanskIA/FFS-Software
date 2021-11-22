#include "IdFileManager.h"
#include "NamesHelper.h"
#include "TextFileInteractionHelper.h"
#include "DbReader.h"

void IdFileManager::RemoveUnusedIds()
{
	TextFileInteractionHelper::ClearTextFile(sampleStatePath);
	TextFileInteractionHelper::ClearTextFile(measurementStatePath);
	TextFileInteractionHelper::ClearTextFile(equipmentStatePath);
	TextFileInteractionHelper::ClearTextFile(measurementParametersStatePath);
	TextFileInteractionHelper::ClearTextFile(equipmentParameterStatePath);
	TextFileInteractionHelper::ClearTextFile(equipmentStatePath);
	TextFileInteractionHelper::ClearTextFile(characteristicStatePath);
	TextFileInteractionHelper::ClearTextFile(characteristicTypeStatePath);
	TextFileInteractionHelper::ClearTextFile(measuringSystemStatePath);
}

void IdFileManager::AddIdsInUse()
{
	AddIdsToSingleFile(dbSamples, sampleStatePath);
	AddIdsToSingleFile(dbCharacteristics, characteristicStatePath);
	AddIdsToSingleFile(dbCharacteristicTypes, characteristicTypeStatePath);
	AddIdsToSingleFile(dbEquipments, equipmentStatePath);
	AddIdsToSingleFile(dbEquipmentParameters, equipmentParameterStatePath);
	AddIdsToSingleFile(dbMeasurements, measurementStatePath);
	AddIdsToSingleFile(dbMeasurementParameters, measurementParametersStatePath);
	AddIdsToSingleFile(dbMeasuringSystems, measuringSystemStatePath);
}

void IdFileManager::AddIdsToSingleFile(QString tableName, QString stateFilePath)
{
	QString sqlReadRequest = "SELECT id FROM %1";
	QSqlQuery query = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlReadRequest.arg(tableName));

	while (query.next())
	{
		TextFileInteractionHelper::WriteIdToTextFile(query.value(0).toInt(), stateFilePath);
	}
}