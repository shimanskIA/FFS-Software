#include "MeasurementAddService.h"
#include "DbWriter.h"

bool MeasurementAddService::AddMeasurementRequestReceiver(MeasurementContext* measurement)
{
	QVariant tableContext;
	tableContext.setValue<MeasurementContext*>(measurement);
	DbWriter* dbWriter = new DbWriter();
	bool isRowAdded = dbWriter->AddRow(tableContext);

	if (isRowAdded)
	{
		measurement->IncrementId();
		return true;
	}

	return false;
}

Q_DECLARE_METATYPE(MeasurementContext*);