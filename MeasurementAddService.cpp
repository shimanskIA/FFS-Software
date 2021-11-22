#include "MeasurementAddService.h"
#include "DbWriter.h"

bool MeasurementAddService::AddMeasurementRequestReceiver(MeasurementContext* measurement)
{
	QVariant tableContext;
	tableContext.setValue<MeasurementContext*>(measurement);
	bool isRowAdded = DbWriter::GetDbWriterInstance().AddRow(tableContext);

	if (isRowAdded)
	{
		measurement->IncrementId();
		return true;
	}

	return false;
}

Q_DECLARE_METATYPE(MeasurementContext*);