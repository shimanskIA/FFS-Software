#include "MeasuringSystemAddService.h"
#include "DbWriter.h"

bool MeasuringSystemAddService::AddMeasuringSystemRequestReceiver(MeasuringSystemContext* measuringSystem)
{
	QVariant tableContext;
	tableContext.setValue<MeasuringSystemContext*>(measuringSystem);
	bool isRowAdded = DbWriter::GetDbWriterInstance().AddRow(tableContext);

	if (isRowAdded)
	{
		measuringSystem->IncrementId();
		return true;
	}

	return false;
}

Q_DECLARE_METATYPE(MeasuringSystemContext*);