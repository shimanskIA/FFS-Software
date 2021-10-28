#include "CharacteristicAddService.h"
#include "TableWriter.h"
#include "DbEditor.h"
#include "NamesHelper.h"

void CharacteristicAddService::ShowAllElementsTableRequestReceiver(QString tableName, QTableView* tableView)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->RouteMajorRequest(tableName, tableView);
}

void CharacteristicAddService::AddCharacteristicRequestReceiver(CharacteristicAddForm* view)
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

		QVariant tableContext;
		tableContext.setValue<CharacteristicsContext*>(characteristic);
		DbEditor* dbEditor = new DbEditor();
		bool isRowAdded = dbEditor->AddRow(tableContext);
		view->SetIsRowAdded(isRowAdded);
		if (isRowAdded)
		{
			characteristic->IncrementId();
		}
	}
}

Q_DECLARE_METATYPE(CharacteristicsContext*);