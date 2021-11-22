#include "SampleAddService.h"
#include "DbWriter.h"

bool SampleAddService::AddSampleRequestReceiver(SampleContext* sample)
{
	QVariant tableContext;
	tableContext.setValue<SampleContext*>(sample);
	bool isRowAdded = DbWriter::GetDbWriterInstance().AddRow(tableContext);

	if (isRowAdded)
	{
		sample->IncrementId();
		return true;
	}

	return false;
}

Q_DECLARE_METATYPE(SampleContext*);