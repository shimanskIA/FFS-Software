#include "FFSDatabaseInterfaceFormController.h"
#include "FFSDatabaseInterfaceService.h"

FFSDatabaseInterfaceFormController::FFSDatabaseInterfaceFormController()
{

}

void FFSDatabaseInterfaceFormController::ManageFileImportRequest(QString fileName)
{
	FFSDatabaseInterfaceService::ImportRequestReceiver(fileName);
}

void FFSDatabaseInterfaceFormController::ManageShowMeasurementTableRequest(Ui::FFSDatabaseInterfaceClass ui)
{
	FFSDatabaseInterfaceService::ShowMeasurementTableRequestReceiver(ui);
}

void FFSDatabaseInterfaceFormController::ManageShowSampleTableRequest(Ui::FFSDatabaseInterfaceClass ui)
{
	FFSDatabaseInterfaceService::ShowSampleTableRequestReceiver(ui);
}

void FFSDatabaseInterfaceFormController::ManageShowEquipmentTableRequest(Ui::FFSDatabaseInterfaceClass ui)
{
	FFSDatabaseInterfaceService::ShowEquipmentTableRequestReceiver(ui);
}

void FFSDatabaseInterfaceFormController::ManageShowMeasuringSystemTableRequest(Ui::FFSDatabaseInterfaceClass ui)
{
	FFSDatabaseInterfaceService::ShowMeasuringSystemTableRequestReceiver(ui);
}

void FFSDatabaseInterfaceFormController::ManageShowCharacteristicTypesTableRequest(Ui::FFSDatabaseInterfaceClass ui)
{
	FFSDatabaseInterfaceService::ShowCharacteristicTypesTableRequestReceiver(ui);
}

void FFSDatabaseInterfaceFormController::ManageShowCharacteristicsTableRequest(Ui::FFSDatabaseInterfaceClass ui)
{
	FFSDatabaseInterfaceService::ShowCharacteristicsTableRequestReceiver(ui);
}

void FFSDatabaseInterfaceFormController::ManageLoadDataToSubtableRequest(Ui::FFSDatabaseInterfaceClass ui, QTableView* tableView, QString majorTableName, QString minorTableName, int majorTableId)
{
	FFSDatabaseInterfaceService::LoadDataToSubtableRequestReceiver(ui, tableView, majorTableName, minorTableName, majorTableId);
}