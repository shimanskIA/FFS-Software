#include "FFSDatabaseInterfaceService.h"
#include "DbImporter.h"
#include "DbEditor.h"
#include "IdFileManager.h"
#include "DbConnection.h"

void FFSDatabaseInterfaceService::ImportRequestReceiver(QString fileLink)
{
	DbContext* dbContext = new DbContext();
	RawDataParser* rawDataParser = new RawDataParser(fileLink);
	DbImporter *dbImporter = new DbImporter(dbContext, rawDataParser);
	dbImporter->ImportToDatabase();
}

void FFSDatabaseInterfaceService::DeleteRowRequestReceiver(QString tableName, int selectedId)
{
	DbEditor* dbEditor = new DbEditor();
	dbEditor->DeleteFromDatabase(tableName, selectedId);
}

bool FFSDatabaseInterfaceService::UpdateTableRequestReceiver(QString tableName, QString columnName, QVariant cellValue, int selectedId)
{
	DbEditor* dbEditor = new DbEditor();
	return dbEditor->UpdateRow(tableName, columnName, cellValue, selectedId);
}

bool FFSDatabaseInterfaceService::ReadAbscissaRequestReceiver(int selectedId, QVector<double>& x)
{
	DbReader* dbReader = new DbReader();
	return dbReader->ReadAbscissaFromDatabase(selectedId, x);
}

bool FFSDatabaseInterfaceService::ReadOrdinateRequestReceiver(int selectedId, QVector<double>& y)
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