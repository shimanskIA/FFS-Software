#include "FFSDatabaseInterfaceService.h"
#include "DbImporter.h"
#include "DbEditor.h"
#include "IdFileManager.h"

void FFSDatabaseInterfaceService::ImportRequestReceiver(QString fileLink)
{
	DbContext* dbContext = new DbContext();
	RawDataParser* rawDataParser = new RawDataParser(fileLink);
	DbImporter *dbImporter = new DbImporter(dbContext, rawDataParser);
	dbImporter->ImportToDatabase();
}

void FFSDatabaseInterfaceService::DeleteRowRequestReceiver(QTableView* tableView, QString tableName)
{
	DbEditor* dbEditor = new DbEditor();
	dbEditor->DeleteRow(tableView, tableName);
}

void FFSDatabaseInterfaceService::UpdateTableRequestReceiver(QVariant cellValue, QString tableName, QTableView* tableView)
{
	DbEditor* dbEditor = new DbEditor();
	dbEditor->UpdateRow(cellValue, tableName, tableView);
}

void FFSDatabaseInterfaceService::RemoveUnusedIdsRequestReceiver()
{
	IdFileManager* idFileManager = new IdFileManager();
	idFileManager->RemoveUnusedIds();
	idFileManager->AddIdsInUse();
}