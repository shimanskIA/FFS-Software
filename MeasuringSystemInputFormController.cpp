#include "MeasuringSystemInputFormController.h"

void MeasuringSystemInputFormController::ManageContinueButtonActivity(MeasuringSystemInputForm* view)
{
	auto ui = view->GetUI();
	if (ui.NameInput->text() != "" &&
		ui.MainContributorInput->text() != "")
	{
		ui.continueButton->setDisabled(false);
	}
	else
	{
		ui.continueButton->setDisabled(true);
	}
}