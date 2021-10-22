#include "FFSDatabaseInterfaceService.h"
#include "DbImporter.h"
#include "TableWriter.h"

void FFSDatabaseInterfaceService::ImportRequestReceiver(QString fileLink)
{
	DbContext* dbContext = new DbContext();
	RawDataParser* rawDataParser = new RawDataParser(fileLink);
	DbImporter *dbImporter = new DbImporter(dbContext, rawDataParser);
	dbImporter->ImportToDatabase();
}

void FFSDatabaseInterfaceService::ShowMeasurementTableRequestReceiver(QTableView* tableView)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->FillMeasurementsTable(tableView);
}

void FFSDatabaseInterfaceService::ShowSampleTableRequestReceiver(QTableView* tableView)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->FillSamplesTable(tableView);
}

void FFSDatabaseInterfaceService::ShowEquipmentTableRequestReceiver(QTableView* tableView)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->FillEquipmentsTable(tableView);
}

void FFSDatabaseInterfaceService::ShowMeasuringSystemTableRequestReceiver(QTableView* tableView)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->FillMeasuringSystemsTable(tableView);
}

void FFSDatabaseInterfaceService::ShowCharacteristicTypesTableRequestReceiver(QTableView* tableView)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->FillCharacteristicTypesTable(tableView);
}

void FFSDatabaseInterfaceService::ShowCharacteristicsTableRequestReceiver(QTableView* tableView)
{
	TableWriter* tableWriter = new TableWriter();
	QString sqlReadRequest = "SELECT * FROM characteristics";
	tableWriter->FillCharacteristicsTable(tableView, sqlReadRequest);
}

void FFSDatabaseInterfaceService::LoadDataToSubtableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui, QTableView* tableView, QString majorTableName, QString minorTableName, int majorTableId)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->RouteRequest(ui, tableView, majorTableName, minorTableName, majorTableId);
}