#include "CharacteristicAddFormController.h"
#include "CharacteristicAddService.h"
#include "TableWriter.h"
#include "NamesHelper.h"

void CharacteristicAddFormController::ManageAddCharacteristicRequest(CharacteristicAddForm* view)
{
	bool finalResult = true;
	QString channel = view->GetUI().ChannelInput->toPlainText();
	QString x = view->GetUI().XInput->toPlainText();
	QString y = view->GetUI().YInput->toPlainText();
	bool convertionResult;
	int numberOfPoints = view->GetUI().NumberOfPointsInput->toPlainText().toInt(&convertionResult);
	finalResult = finalResult && convertionResult;
	double binTime = view->GetUI().BinTimeInput->toPlainText().toDouble(&convertionResult);
	finalResult = finalResult && convertionResult;
	double weight = view->GetUI().WeightInput->toPlainText().toDouble(&convertionResult);
	finalResult = finalResult && convertionResult;
	bool isRowAdded = false;

	if (finalResult)
	{
		CharacteristicsContext* characteristic = new CharacteristicsContext(characteristicStatePath);

		characteristic->SetChannel(channel);
		characteristic->SetBinTime(binTime);
		characteristic->SetNumberOfPoints(numberOfPoints);
		characteristic->SetX(x);
		characteristic->SetY(y);
		characteristic->SetWeight(weight);

		if (view->GetFKMeasurement() == 0)
		{
			int id = view->GetChosenMeasurementsTableModel()->data(view->GetChosenMeasurementsTableModel()->index(0, 0)).toInt();
			view->SetFKMeasurement(id);
		}

		if (view->GetFKCharacteristicType() == 0)
		{
			int id = view->GetChosenCharacteristicTypesTableModel()->data(view->GetChosenCharacteristicTypesTableModel()->index(0, 0)).toInt();
			view->SetFKCharacteristicType(id);
		}

		characteristic->SetFKMeasurement(view->GetFKMeasurement());
		characteristic->SetFKCharacteristicType(new CharacteristicTypeContext(view->GetFKCharacteristicType()));
		isRowAdded = CharacteristicAddService::AddCharacteristicRequestReceiver(characteristic);
	}

	view->SetIsRowAdded(isRowAdded);
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
		ManageFillIndependentTableRequest(tableName, tableView);
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