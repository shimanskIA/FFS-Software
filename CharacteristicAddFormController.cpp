#include "CharacteristicAddFormController.h"
#include "CharacteristicAddService.h"
#include "TableWriter.h"
#include "NamesHelper.h"

void CharacteristicAddFormController::ManageAddCharacteristicRequest(CharacteristicAddForm* view)
{
	bool finalResult = true;
	QString name;
	QString channel = view->GetUI().ChannelInput->text();
	QString x = view->GetUI().XInput->text();
	QString y = view->GetUI().YInput->text();
	int numberOfPoints = view->GetUI().NumberOfPointsInput->value();
	double binTime = view->GetUI().BinTimeInput->value();
	double weight = view->GetUI().WeightInput->value();

	bool isRowAdded = false;

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

	QString sqlReadRequest = "SELECT name, file_link, date FROM measurements WHERE id = %1";
	QSqlQuery query = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlReadRequest.arg(view->GetFKMeasurement()));
	query.next();
	name = (query.value(0).toString().trimmed() + 
		query.value(1).toString().trimmed().split('/').last() + 
		query.value(2).toString().trimmed()).toUpper();
	characteristic->SetName(name);

	if (view->GetFKCharacteristicType() == 0)
	{
		int id = view->GetChosenCharacteristicTypesTableModel()->data(view->GetChosenCharacteristicTypesTableModel()->index(0, 0)).toInt();
		view->SetFKCharacteristicType(id);
	}

	characteristic->SetFKMeasurement(view->GetFKMeasurement());
	characteristic->SetFKCharacteristicType(new CharacteristicTypeContext(view->GetFKCharacteristicType()));
	isRowAdded = CharacteristicAddService::AddCharacteristicRequestReceiver(characteristic);

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
	auto ui = view->GetUI();
	int selectedRow = ui.allElementsTable->currentIndex().row();
	FFSTableModel* chosenElementsTableModel = (FFSTableModel*)ui.chosenElementsTable->model();
	FFSTableModel* allElementsTableModel = (FFSTableModel*)ui.allElementsTable->model();
	chosenElementsTableModel->appendRow(allElementsTableModel->takeRow(selectedRow));

	for (int j = 0; j < allElementsTableModel->columnCount(); j++)
	{
		chosenElementsTableModel->setHeaderData(j, Qt::Horizontal, allElementsTableModel->headerData(j, Qt::Horizontal));
	}

	if (view->GetIsFirstTime())
	{
		view->SetTableSettings(ui.chosenElementsTable);
		view->SetIsFirstTime(false);
	}
	ui.chosenElementsTable->setColumnHidden(0, true);

	if ((view->GetChosenMeasurementsTableModel()->rowCount() > 0 || view->GetFKMeasurement() > 0) &&
		(view->GetChosenCharacteristicTypesTableModel()->rowCount() > 0 || view->GetFKCharacteristicType() > 0) &&
		ui.ChannelInput->text() != "" &&
		ui.XInput->text() != "" &&
		ui.YInput->text() != "")
	{
		ui.AddCharacteristicButton->setDisabled(false);
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

void CharacteristicAddFormController::ManageAddButtonActivity(CharacteristicAddForm* view)
{
	auto ui = view->GetUI();
	if ((view->GetChosenMeasurementsTableModel()->rowCount() > 0 || view->GetFKMeasurement() > 0) &&
		(view->GetChosenCharacteristicTypesTableModel()->rowCount() > 0 || view->GetFKCharacteristicType() > 0) &&
		ui.ChannelInput->text() != "" &&
		ui.XInput->text() != "" &&
		ui.YInput->text() != "")
	{
		ui.AddCharacteristicButton->setDisabled(false);
	}
	else
	{
		ui.AddCharacteristicButton->setDisabled(true);
	}
}