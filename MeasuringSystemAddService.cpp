#include "MeasuringSystemAddService.h"
#include "DbEditor.h"

bool MeasuringSystemAddService::AddMeasuringSystemRequestReceiver(MeasuringSystemContext* measuringSystem)
{
	QVariant tableContext;
	tableContext.setValue<MeasuringSystemContext*>(measuringSystem);
	DbEditor* dbEditor = new DbEditor();
	bool isRowAdded = dbEditor->AddRow(tableContext);

	if (isRowAdded)
	{
		measuringSystem->IncrementId();
		return true;
	}

	return false;
}

Q_DECLARE_METATYPE(MeasuringSystemContext*);