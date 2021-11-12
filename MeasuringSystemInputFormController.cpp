#include "MeasuringSystemInputFormController.h"

void MeasuringSystemInputFormController::ManageContinueButtonActivity(MeasuringSystemInputForm* view)
{
	auto ui = view->GetUI();
	if (ui.NameInput->toPlainText() != "" &&
		ui.MainContributorInput->toPlainText() != "")
	{
		ui.continueButton->setDisabled(false);
	}
	else
	{
		ui.continueButton->setDisabled(true);
	}
}