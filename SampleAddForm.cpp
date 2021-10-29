#include "SampleAddForm.h"
#include "SampleAddFormController.h"

SampleAddForm::SampleAddForm(QWidget* parent) : BaseAddForm(parent)
{
	ui.setupUi(this);
	this->setFixedSize(601, 188);
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