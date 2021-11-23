#include "SampleAddForm.h"
#include "SampleAddFormController.h"

SampleAddForm::SampleAddForm(QWidget* parent) : BaseAddForm(parent)
{
	ui.setupUi(this);
	this->setFixedSize(601, 188);
	connect(ui.AddSampleButton, SIGNAL(clicked()), this, SLOT(addSample()));
	connect(ui.NameInput, SIGNAL(textChanged()), this, SLOT(manageAddButtonActivity()));
}

void SampleAddForm::manageAddButtonActivity()
{
	SampleAddFormController::ManageAddButtonActivity(this);
}

void SampleAddForm::addSample()
{
	SampleAddFormController::ManageAddSampleRequest(this);
}

Ui::SampleAddFormClass SampleAddForm::GetUI()
{
	return this->ui;
}