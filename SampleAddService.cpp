#include "SampleAddService.h"
#include "DbEditor.h"

bool SampleAddService::AddSampleRequestReceiver(SampleContext* sample)
{
	QVariant tableContext;
	tableContext.setValue<SampleContext*>(sample);
	DbEditor* dbEditor = new DbEditor();
	bool isRowAdded = dbEditor->AddRow(tableContext);

	if (isRowAdded)
	{
		sample->IncrementId();
		return true;
	}

	return false;
}

Q_DECLARE_METATYPE(SampleContext*);