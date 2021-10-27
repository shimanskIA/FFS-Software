#include "FFSDatabaseInterfaceService.h"
#include "DbImporter.h"
#include "TableWriter.h"
#include "DbEditor.h"
#include "IdFileManager.h"
#include "WindowManager.h"

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

void FFSDatabaseInterfaceService::ShowMajorTableRequestReceiver(QString tableName, QTableView* tableView)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->RouteMajorRequest(tableName, tableView);
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

void FFSDatabaseInterfaceService::LoadDataToSubtableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui, QTableView* tableView, QString majorTableName, QString minorTableName, int majorTableId)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->RouteRequest(ui, tableView, majorTableName, minorTableName, majorTableId);
}

void FFSDatabaseInterfaceService::ShowAddViewRequestReceiver(QString tableName, FFSDatabaseInterface* view, int fk1, int fk2)
{
	WindowManager* windowMananger = new WindowManager();
	windowMananger->ManageWindows(tableName, view, fk1, fk2);
}