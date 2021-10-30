#include "MeasurementAddService.h"
#include "DbEditor.h"

bool MeasurementAddService::AddMeasurementRequestReceiver(MeasurementContext* measurement)
{
	QVariant tableContext;
	tableContext.setValue<MeasurementContext*>(measurement);
	DbEditor* dbEditor = new DbEditor();
	bool isRowAdded = dbEditor->AddRow(tableContext);

	if (isRowAdded)
	{
		measurement->IncrementId();
		return true;
	}

	return false;
}

Q_DECLARE_METATYPE(MeasurementContext*);