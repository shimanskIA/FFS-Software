#include "MeasuringSystemAddFormController.h"
#include "MeasuringSystemAddService.h"
#include "TableWriter.h"
#include "NamesHelper.h"
#include "MeasuringSystemContext.h"
#include "ErrorForm.h"

void MeasuringSystemAddFormController::ManageAddMeasuringSystemRequest(MeasuringSystemAddForm* view)
{
	auto ui = view->GetUI();
	QString name = ui.NameInput->text();
	QString description = ui.DescriptionInput->text();
	QString mainContributorName = ui.MainContributorNameInput->text();
	bool isRowAdded = false;
	MeasuringSystemContext* measuringSystem = new MeasuringSystemContext(measuringSystemStatePath);
	measuringSystem->SetName(name);
	measuringSystem->SetDescription(description);
	measuringSystem->SetMainContributorName(mainContributorName);
	FFSTableModel* chosenElementsTableModel = (FFSTableModel*)ui.chosenElementsTable->model();

	for (int i = 0; i < chosenElementsTableModel->rowCount(); i++)
	{
		BindingContext* binding = new BindingContext();
		int fk_equipment = chosenElementsTableModel->data(chosenElementsTableModel->index(i, 0)).toInt();
		binding->SetFKEquipment(fk_equipment);
		binding->SetFKMeasuringSystem(measuringSystem->GetId());
		measuringSystem->AddNewBinding(binding);
	}

	isRowAdded = MeasuringSystemAddService::AddMeasuringSystemRequestReceiver(measuringSystem);
	view->SetIsRowAdded(isRowAdded);

	if (isRowAdded)
	{
		view->close();
	}
	else
	{
		ErrorForm* errorForm = new ErrorForm("Measuring system with these credentials already exists.");
		errorForm->show();
		ui.NameInput->setText("");
		ui.MainContributorNameInput->setText("");
	}
}

void MeasuringSystemAddFormController::ManageShowAllElementsTableRequest(QTableView* tableView)
{
	ManageFillIndependentTableRequest("equipment", tableView);
}

void MeasuringSystemAddFormController::ManageChooseUpperElementRequest(MeasuringSystemAddForm* view)
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

	view->GetUI().chosenElementsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	view->GetUI().chosenElementsTable->setColumnHidden(0, true);
}

void MeasuringSystemAddFormController::ManageCancelChooseRequest(MeasuringSystemAddForm* view)
{
	int selectedRow = view->GetUI().chosenElementsTable->currentIndex().row();
	FFSTableModel* chosenElementsTableModel = (FFSTableModel*)view->GetUI().chosenElementsTable->model();
	FFSTableModel* allElementsTableModel = (FFSTableModel*)view->GetUI().allElementsTable->model();
	allElementsTableModel->appendRow(chosenElementsTableModel->takeRow(selectedRow));
	allElementsTableModel->sort(0, Qt::AscendingOrder);
}

void MeasuringSystemAddFormController::ManageAddButtonActivity(MeasuringSystemAddForm* view)
{
	auto ui = view->GetUI();
	if (ui.NameInput->text() != "" &&
		ui.MainContributorNameInput->text() != "")
	{
		ui.AddMeasuringSystemButton->setDisabled(false);
	}
	else
	{
		ui.AddMeasuringSystemButton->setDisabled(true);
	}
}