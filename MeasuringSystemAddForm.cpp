#include "MeasuringSystemAddForm.h"

MeasuringSystemAddForm::MeasuringSystemAddForm(QWidget* parent) : BaseAddForm(parent)
{
	ui.setupUi(this);
	connect(ui.AddMSButton, SIGNAL(clicked()), this, SLOT(addMeasuringSystem()));
}

void MeasuringSystemAddForm::addMeasuringSystem()
{
	this->close();
}