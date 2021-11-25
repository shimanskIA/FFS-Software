#include "SampleAddFormController.h"
#include "SampleAddService.h"
#include "NamesHelper.h"
#include "ErrorForm.h"

void SampleAddFormController::ManageAddSampleRequest(SampleAddForm* view)
{
	QString name = view->GetUI().NameInput->text();
	QString description = view->GetUI().DescriptionInput->text();
	SampleContext* sample = new SampleContext(sampleStatePath);
	sample->SetName(name);
	sample->SetDescription(description);
	bool isRowAdded = SampleAddService::AddSampleRequestReceiver(sample);
	view->SetIsRowAdded(isRowAdded);

	if (isRowAdded)
	{
		view->close();
	}
	else
	{
		ErrorForm* errorForm = new ErrorForm("Sample with these name and description already exists in database.");
		errorForm->show();
		view->GetUI().NameInput->setText("");
		view->GetUI().DescriptionInput->setText("");
	}
}

void SampleAddFormController::ManageAddButtonActivity(SampleAddForm* view)
{
	auto ui = view->GetUI();
	if (ui.NameInput->text() != "")
	{
		ui.AddSampleButton->setDisabled(false);
	}
	else
	{
		ui.AddSampleButton->setDisabled(true);
	}
}