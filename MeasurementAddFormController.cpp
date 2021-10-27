#include "MeasurementAddFormController.h"
#include "MeasurementAddService.h"

void MeasurementAddFormController::ManageAddMeasurementRequest(MeasurementAddForm* view)
{
	MeasurementAddService::AddMeasurementRequestReceiver(view);
}

void MeasurementAddFormController::ManageShowAllElementsTableRequest(QString tableName, QTableView* tableView, MeasurementAddForm* view, bool firstLoad)
{
	tableName.chop(1);

	if (tableName == "measuring system")
	{
		view->GetUI().allElementsTable->setModel(view->GetAllMeasuringSystemsTableModel());
		view->GetUI().chosenElementsTable->setModel(view->GetChosenMeasuringSystemsTableModel());
	}
	else
	{
		view->GetUI().allElementsTable->setModel(view->GetAllSamplesTableModel());
		view->GetUI().chosenElementsTable->setModel(view->GetChosenSamplesTableModel());
	}

	if (firstLoad)
	{
		MeasurementAddService::ShowAllElementsTableRequestReceiver(tableName, tableView);
	}
}

void MeasurementAddFormController::ManageChooseUpperElementRequest(MeasurementAddForm* view)
{
	int selectedRow = view->GetUI().allElementsTable->currentIndex().row();
	FFSTableModel* chosenElementsTableModel = (FFSTableModel*)view->GetUI().chosenElementsTable->model(); 
	FFSTableModel* allElementsTableModel = (FFSTableModel*)view->GetUI().allElementsTable->model();
	chosenElementsTableModel->appendRow(allElementsTableModel->takeRow(selectedRow));

	for (int j = 0; j < allElementsTableModel->columnCount(); j++)
	{
		chosenElementsTableModel->setHeaderData(j, Qt::Horizontal, allElementsTableModel->headerData(j, Qt::Horizontal));
	}

	if (view->GetIsFirstTime())
	{
		view->SetTableSettings(view->GetUI().chosenElementsTable);
		view->SetIsFirstTime(false);
	}
	view->GetUI().chosenElementsTable->setColumnHidden(0, true);

	if ((view->GetChosenMeasuringSystemsTableModel()->rowCount() > 0 || view->GetFKMeasuringSystem() > 0) && 
		(view->GetChosenSamplesTableModel()->rowCount() > 0 || view->GetFKSample() > 0))
	{
		view->GetUI().AddMeasurementButton->setDisabled(false);
	}
}

void MeasurementAddFormController::ManageCancelChooseRequest(MeasurementAddForm* view)
{
	int selectedRow = view->GetUI().chosenElementsTable->currentIndex().row();
	FFSTableModel* chosenElementsTableModel = (FFSTableModel*)view->GetUI().chosenElementsTable->model();
	FFSTableModel* allElementsTableModel = (FFSTableModel*)view->GetUI().allElementsTable->model();
	allElementsTableModel->appendRow(chosenElementsTableModel->takeRow(selectedRow));
	allElementsTableModel->sort(0, Qt::AscendingOrder);
	view->GetUI().AddMeasurementButton->setDisabled(true);
}