#include "EquipmentAddFormController.h"
#include "EquipmentAddService.h"
#include "NamesHelper.h"
#include "FFSTableModel.h"
#include "TableWriter.h"

void EquipmentAddFormController::ManageAddEquipmentRequest(EquipmentAddForm* view)
{
	QString name = view->GetUI().NameInput->toPlainText();
	QString description = view->GetUI().DescriptionInput->toPlainText();
	EquipmentContext* equipmentItem = new EquipmentContext(equipmentStatePath);
	equipmentItem->SetName(name);
	equipmentItem->SetDescription(description);

	if (view->GetFKMeasuringSystem() != 0)
	{
		BindingContext* binding = new BindingContext();
		binding->SetFKMeasuringSystem(view->GetFKMeasuringSystem());
		binding->SetFKEquipment(equipmentItem->GetId());
		equipmentItem->SetBinding(binding);
	}

	bool isRowAdded =  EquipmentAddService::AddEquipmentRequestReceiver(equipmentItem);
	view->SetIsRowAdded(isRowAdded);
}

void EquipmentAddFormController::ManageAddExistingEquipmentRequest(EquipmentAddForm* view, int fk_measuring_system)
{
	QList<BindingContext*> bindings;

	for (int i = 0; i < view->GetUI().chosenEquipmentTable->model()->rowCount(); i++)
	{
		BindingContext* binding = new BindingContext();
		binding->SetFKMeasuringSystem(fk_measuring_system);
		binding->SetFKEquipment(view->GetUI().chosenEquipmentTable->model()->index(i, 0).data().toInt());
		bindings.append(binding);
	}

	EquipmentAddService::AddExistingEquipmentRequestReceiver(bindings, fk_measuring_system);
	view->SetIsRowAdded(true);
}

void EquipmentAddFormController::ManageShowAllElementsTableRequest(QTableView* tableView)
{
	ManageFillIndependentTableRequest("equipment", tableView);
}

void EquipmentAddFormController::ManageChooseUpperElementRequest(EquipmentAddForm* view)
{
	int selectedRow = view->GetUI().allEquipmentTable->currentIndex().row();
	FFSTableModel* chosenElementsTableModel = (FFSTableModel*)view->GetUI().chosenEquipmentTable->model();
	FFSTableModel* allElementsTableModel = (FFSTableModel*)view->GetUI().allEquipmentTable->model();
	chosenElementsTableModel->appendRow(allElementsTableModel->takeRow(selectedRow));

	for (int j = 0; j < allElementsTableModel->columnCount(); j++)
	{
		chosenElementsTableModel->setHeaderData(j, Qt::Horizontal, allElementsTableModel->headerData(j, Qt::Horizontal));
	}

	view->GetUI().chosenEquipmentTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	view->GetUI().chosenEquipmentTable->setColumnHidden(0, true);
	view->GetUI().AddEquipmentButton->setDisabled(false);
}

void EquipmentAddFormController::ManageCancelChooseRequest(EquipmentAddForm* view)
{
	int selectedRow = view->GetUI().chosenEquipmentTable->currentIndex().row();
	FFSTableModel* chosenElementsTableModel = (FFSTableModel*)view->GetUI().chosenEquipmentTable->model();
	FFSTableModel* allElementsTableModel = (FFSTableModel*)view->GetUI().allEquipmentTable->model();
	allElementsTableModel->appendRow(chosenElementsTableModel->takeRow(selectedRow));
	allElementsTableModel->sort(0, Qt::AscendingOrder);

	if (chosenElementsTableModel->rowCount() == 0)
	{
		view->GetUI().AddEquipmentButton->setDisabled(true);
	}
}

void EquipmentAddFormController::ManageChooseExistingEquipmentRequest(EquipmentAddForm* view, int checkboxState)
{
	if (checkboxState == Qt::Checked)
	{
		auto ui = view->GetUI();
		ui.NameInput->setDisabled(true);
		ui.DescriptionInput->setDisabled(true);
		ui.allEquipmentTable->setDisabled(false);
		ui.chosenEquipmentTable->setDisabled(false);
		view->SetIsExistingEquipmentChosen(true);

		if (view->GetUI().chosenEquipmentTable->model()->rowCount() == 0)
		{
			ui.AddEquipmentButton->setDisabled(true);
		}
		else
		{
			ui.AddEquipmentButton->setDisabled(false);
		}

		if (view->GetIsFirstTime())
		{
			view->SetTableSettings(ui.allEquipmentTable);
			view->SetTableSettings(ui.chosenEquipmentTable);
			TableWriter::GetTableWriterInstance().FillExistingEquipmentTable(view, view->GetFKMeasuringSystem());
			view->SetIsFirstTime(false);
		}
	}
	else
	{
		auto ui = view->GetUI();
		ui.NameInput->setDisabled(false);
		ui.DescriptionInput->setDisabled(false);

		if (ui.NameInput->toPlainText() != "")
		{
			ui.AddEquipmentButton->setDisabled(false);
		}
		else
		{
			ui.AddEquipmentButton->setDisabled(true);
		}

		ui.allEquipmentTable->setDisabled(true);
		ui.chosenEquipmentTable->setDisabled(true);
		view->SetIsExistingEquipmentChosen(false);
	}
}

void EquipmentAddFormController::ManageAddButtonActivity(EquipmentAddForm* view)
{
	auto ui = view->GetUI();
	if (ui.NameInput->toPlainText() != "")
	{
		ui.AddEquipmentButton->setDisabled(false);
	}
	else
	{
		ui.AddEquipmentButton->setDisabled(true);
	}
}