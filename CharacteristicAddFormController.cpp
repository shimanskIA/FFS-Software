#include "CharacteristicAddFormController.h"
#include "CharacteristicAddService.h"

void CharacteristicAddFormController::ManageAddCharacteristicRequest(CharacteristicAddForm* view)
{
	CharacteristicAddService::AddCharacteristicRequestReceiver(view);
}

void CharacteristicAddFormController::ManageShowAllElementsTableRequest(QString tableName, QTableView* tableView, CharacteristicAddForm* view, bool firstLoad)
{
	tableName.chop(1);

	if (tableName == "measurement")
	{
		view->GetUI().allElementsTable->setModel(view->GetAllMeasurementsTableModel());
		view->GetUI().chosenElementsTable->setModel(view->GetChosenMeasurementsTableModel());
	}
	else
	{
		view->GetUI().allElementsTable->setModel(view->GetAllCharacteristicTypesTableModel());
		view->GetUI().chosenElementsTable->setModel(view->GetChosenCharacteristicTypesTableModel());
	}

	if (firstLoad)
	{
		CharacteristicAddService::ShowAllElementsTableRequestReceiver(tableName, tableView);
	}
}

void CharacteristicAddFormController::ManageChooseUpperElementRequest(CharacteristicAddForm* view)
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

	if ((view->GetChosenMeasurementsTableModel()->rowCount() > 0 || view->GetFKMeasurement() > 0) &&
		(view->GetChosenCharacteristicTypesTableModel()->rowCount() > 0 || view->GetFKCharacteristicType() > 0))
	{
		view->GetUI().AddCharacteristicButton->setDisabled(false);
	}
}

void CharacteristicAddFormController::ManageCancelChooseRequest(CharacteristicAddForm* view)
{
	int selectedRow = view->GetUI().chosenElementsTable->currentIndex().row();
	FFSTableModel* chosenElementsTableModel = (FFSTableModel*)view->GetUI().chosenElementsTable->model();
	FFSTableModel* allElementsTableModel = (FFSTableModel*)view->GetUI().allElementsTable->model();
	allElementsTableModel->appendRow(chosenElementsTableModel->takeRow(selectedRow));
	allElementsTableModel->sort(0, Qt::AscendingOrder);
	view->GetUI().AddCharacteristicButton->setDisabled(true);
}