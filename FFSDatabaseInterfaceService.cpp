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

void FFSDatabaseInterfaceService::ShowMeasurementTableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->FillMeasurementsTable(ui);
}

void FFSDatabaseInterfaceService::ShowSampleTableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->FillSamplesTable(ui);
}

void FFSDatabaseInterfaceService::ShowEquipmentTableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->FillEquipmentsTable(ui);
}

void FFSDatabaseInterfaceService::ShowMeasuringSystemTableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->FillMeasuringSystemsTable(ui);
}

void FFSDatabaseInterfaceService::LoadDataToSubtableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui, QTableView* tableView, QString majorTableName, QString minorTableName, int majorTableId)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->RouteRequest(ui, tableView, majorTableName, minorTableName, majorTableId);
}