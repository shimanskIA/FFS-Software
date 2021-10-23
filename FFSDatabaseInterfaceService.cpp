#include "FFSDatabaseInterfaceService.h"
#include "DbImporter.h"
#include "TableWriter.h"
#include "DbEditor.h"
#include "IdFileManager.h"

void FFSDatabaseInterfaceService::ImportRequestReceiver(QString fileLink)
{
	DbContext* dbContext = new DbContext();
	RawDataParser* rawDataParser = new RawDataParser(fileLink);
	DbImporter *dbImporter = new DbImporter(dbContext, rawDataParser);
	dbImporter->ImportToDatabase();
}

void FFSDatabaseInterfaceService::ShowMeasuringSystemTableRequestReceiver(QTableView* tableView)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->FillMeasuringSystemsTable(tableView);
}

void FFSDatabaseInterfaceService::ShowCharacteristicsTableRequestReceiver(QTableView* tableView)
{
	TableWriter* tableWriter = new TableWriter();
	QString sqlReadRequest = "SELECT * FROM characteristics";
	tableWriter->FillCharacteristicsTable(tableView, sqlReadRequest);
}

void FFSDatabaseInterfaceService::ShowMajorTableRequestReceiver(FFSDatabaseInterface* view)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->RouteMajorRequest(view);
}

void FFSDatabaseInterfaceService::DeleteRowRequestReceiver(QTableView* tableView, QString tableName)
{
	DbEditor* dbEditor = new DbEditor();
	dbEditor->DeleteRow(tableView, tableName);
}

void FFSDatabaseInterfaceService::RemoveUnusedIdsRequestReceiver()
{
	IdFileManager* idFileManager = new IdFileManager();
	idFileManager->RemoveUnusedIds();
	idFileManager->AddIdsInUse();
}

void FFSDatabaseInterfaceService::LoadDataToSubtableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui, QTableView* tableView, QString majorTableName, QString minorTableName, int majorTableId)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->RouteRequest(ui, tableView, majorTableName, minorTableName, majorTableId);
}