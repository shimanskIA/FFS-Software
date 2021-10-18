#include "FFSDatabaseInterfaceService.h"
#include "DbImporter.h"
#include "DbConnection.h"
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
	tableWriter->SetTableSettings(ui);
}

void FFSDatabaseInterfaceService::ShowSampleTableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui)
{

}

void FFSDatabaseInterfaceService::ShowEquipmentTableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui)
{

}