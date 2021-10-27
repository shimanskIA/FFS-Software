#include "MeasurementAddService.h"
#include "TableWriter.h"
#include "DbEditor.h"
#include "NamesHelper.h"

void MeasurementAddService::ShowAllElementsTableRequestReceiver(QString tableName, QTableView* tableView)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->RouteMajorRequest(tableName, tableView);
}

void MeasurementAddService::AddMeasurementRequestReceiver(MeasurementAddForm* view)
{
	bool finalResult = true;
	QString name = view->GetUI().NameInput->toPlainText();
	QString date = view->GetUI().DateInput->toPlainText();
	QString file = view->GetUI().FileInput->toPlainText();
	bool convertionResult;
	int repeatCount = view->GetUI().RepeatCountInput->toPlainText().toInt(&convertionResult);
	finalResult = finalResult && convertionResult;
	int kineticsCount = view->GetUI().KineticsCountInput->toPlainText().toInt(&convertionResult);
	finalResult = finalResult && convertionResult;
	int numberOfChannels = view->GetUI().NumberOfChannelsInput->toPlainText().toInt(&convertionResult);
	finalResult = finalResult && convertionResult;
	int numberPositions = view->GetUI().NumberPositionsInput->toPlainText().toInt(&convertionResult);
	finalResult = finalResult && convertionResult;

	if (finalResult)
	{
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

		QVariant tableContext;
		tableContext.setValue<MeasurementContext*>(measurement);
		DbEditor* dbEditor = new DbEditor();
		bool isRowAdded = dbEditor->AddRow(tableContext);
		view->SetIsRowAdded(isRowAdded);
		if (isRowAdded)
		{
			measurement->IncrementId();
		}
	}
}

Q_DECLARE_METATYPE(MeasurementContext*);