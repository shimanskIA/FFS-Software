#include "MeasuringSystemAddService.h"
#include "DbWriter.h"

bool MeasuringSystemAddService::AddMeasuringSystemRequestReceiver(MeasuringSystemContext* measuringSystem)
{
	QVariant tableContext;
	tableContext.setValue<MeasuringSystemContext*>(measuringSystem);
	DbWriter* dbWriter = new DbWriter();
	bool isRowAdded = dbWriter->AddRow(tableContext);

	if (isRowAdded)
	{
		measuringSystem->IncrementId();
		return true;
	}

	return false;
}

Q_DECLARE_METATYPE(MeasuringSystemContext*);