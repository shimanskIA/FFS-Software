#include "MeasurementAddFormController.h"
#include "MeasurementAddService.h"
#include "TableWriter.h"
#include "NamesHelper.h"

void MeasurementAddFormController::ManageAddMeasurementRequest(MeasurementAddForm* view)
{
	bool isRowAdded = false;
	QString file = view->GetUI().FileInput->toPlainText();

	if (file.isEmpty())
	{
		view->SetIsRowAdded(isRowAdded);
		return;
	}

	QString name = view->GetUI().NameInput->toPlainText();
	QString date = view->GetUI().DateInput->text();
	int repeatCount = view->GetUI().RepeatCountInput->value();
	int kineticsCount = view->GetUI().KineticsCountInput->value();
	int numberOfChannels = view->GetUI().NumberOfChannelsInput->value();
	int numberPositions = view->GetUI().NumberPositionsInput->value();

	MeasurementContext* measurement = new MeasurementContext(measurementStatePath);
	measurement->SetName(name);
	measurement->SetDateTime(date);
	measurement->SetFileLink(file);
	measurement->SetRepeatCount(repeatCount);
	measurement->SetKineticsCount(kineticsCount);
	measurement->SetNumberOfChannels(numberOfChannels);
	measurement->SetNumberPositions(numberPositions);

	if (view->GetFKMeasuringSystem() == 0)
	{
		int id = view->GetChosenMeasuringSystemsTableModel()->data(view->GetChosenMeasuringSystemsTableModel()->index(0, 0)).toInt();
		view->SetFKMeasuringSystem(id);
	}

	if (view->GetFKSample() == 0)
	{
		int id = view->GetChosenSamplesTableModel()->data(view->GetChosenSamplesTableModel()->index(0, 0)).toInt();
		view->SetFKSample(id);
	}

	measurement->SetFKMeasuringSystem(view->GetFKMeasuringSystem());
	measurement->SetFKSample(new SampleContext(view->GetFKSample()));
	isRowAdded = MeasurementAddService::AddMeasurementRequestReceiver(measurement);

	view->SetIsRowAdded(isRowAdded);
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
		ManageFillIndependentTableRequest(tableName, tableView);
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