#include "SampleAddService.h"
#include "TextFileInteractionHelper.h"
#include "NamesHelper.h"
#include "SampleContext.h"
#include "DbEditor.h"

void SampleAddService::AddSampleRequestReceiver(SampleAddForm* view)
{
	QString name = view->GetUI().NameInput->toPlainText();
	QString description = view->GetUI().DescriptionInput->toPlainText();
	SampleContext* sample = new SampleContext(sampleStatePath);
	sample->SetName(name);
	sample->SetDescription(description);
	QVariant tableContext;
	tableContext.setValue<SampleContext*>(sample);
	DbEditor* dbEditor = new DbEditor();
	bool isRowAdded = dbEditor->AddRow(tableContext);
	view->SetIsRowAdded(isRowAdded);

	if (isRowAdded)
	{
		sample->IncrementId();
	}
}

Q_DECLARE_METATYPE(SampleContext*);