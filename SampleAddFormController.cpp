#include "SampleAddFormController.h"
#include "SampleAddService.h"
#include "NamesHelper.h"

void SampleAddFormController::ManageAddSampleRequest(SampleAddForm* view)
{
	QString name = view->GetUI().NameInput->toPlainText();
	QString description = view->GetUI().DescriptionInput->toPlainText();
	SampleContext* sample = new SampleContext(sampleStatePath);
	sample->SetName(name);
	sample->SetDescription(description);
	bool isRowAdded = SampleAddService::AddSampleRequestReceiver(sample);
	view->SetIsRowAdded(isRowAdded);
}