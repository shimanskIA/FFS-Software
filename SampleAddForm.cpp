#include "SampleAddForm.h"
#include "SampleAddFormController.h"

SampleAddForm::SampleAddForm(QWidget* parent) : BaseAddForm(parent)
{
	ui.setupUi(this);
	connect(ui.AddSampleButton, SIGNAL(clicked()), this, SLOT(addSample()));
}

void SampleAddForm::addSample()
{
	SampleAddFormController::ManageAddSampleRequest(this);
	this->close();
}

Ui::SampleAddFormClass SampleAddForm::GetUI()
{
	return this->ui;
}