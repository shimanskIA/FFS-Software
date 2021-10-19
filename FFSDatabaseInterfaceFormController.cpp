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

void FFSDatabaseInterfaceFormController::ManageLoadDataToSubtableRequest(Ui::FFSDatabaseInterfaceClass ui, QString majorTableName, QString minorTableName, int majorTableId)
{
	FFSDatabaseInterfaceService::LoadDataToSubtableRequestReceiver(ui, majorTableName, minorTableName, majorTableId);
}