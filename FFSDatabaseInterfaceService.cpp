#include "FFSDatabaseInterfaceService.h"
#include "DbImporter.h"
#include "DbEditor.h"
#include "IdFileManager.h"
#include "DbConnection.h"

OperationStatusMessage* FFSDatabaseInterfaceService::ImportRequestReceiver(QString fileLink)
{
	DbContext* dbContext = new DbContext();
	RawDataParser* rawDataParser = new RawDataParser(fileLink);
	DbImporter *dbImporter = new DbImporter(dbContext, rawDataParser);
	return dbImporter->ImportToDatabase();
}

OperationStatusMessage* FFSDatabaseInterfaceService::DeleteRowRequestReceiver(QString tableName, int selectedId)
{
	DbEditor* dbEditor = new DbEditor();
	return dbEditor->DeleteFromDatabase(tableName, selectedId);
}

OperationStatusMessage* FFSDatabaseInterfaceService::UpdateTableRequestReceiver(QString tableName, QString columnName, QVariant cellValue, int selectedId)
{
	DbEditor* dbEditor = new DbEditor();
	return dbEditor->UpdateRow(tableName, columnName, cellValue, selectedId);
}

OperationStatusMessage* FFSDatabaseInterfaceService::ReadAbscissaRequestReceiver(int selectedId, QVector<double>& x)
{
	DbReader* dbReader = new DbReader();
	return dbReader->ReadAbscissaFromDatabase(selectedId, x);
}

OperationStatusMessage* FFSDatabaseInterfaceService::ReadOrdinateRequestReceiver(int selectedId, QVector<double>& y)
{
	DbReader* dbReader = new DbReader();
	return dbReader->ReadOrdinateFromDatabase(selectedId, y);
}

void FFSDatabaseInterfaceService::RemoveUnusedIdsRequestReceiver()
{
	IdFileManager* idFileManager = new IdFileManager();
	idFileManager->RemoveUnusedIds();
	idFileManager->AddIdsInUse();
}