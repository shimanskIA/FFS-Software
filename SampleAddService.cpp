#include "SampleAddService.h"
#include "DbWriter.h"

bool SampleAddService::AddSampleRequestReceiver(SampleContext* sample)
{
	QVariant tableContext;
	tableContext.setValue<SampleContext*>(sample);
	DbWriter* dbWriter = new DbWriter();
	bool isRowAdded = dbWriter->AddRow(tableContext);

	if (isRowAdded)
	{
		sample->IncrementId();
		return true;
	}

	return false;
}

Q_DECLARE_METATYPE(SampleContext*);