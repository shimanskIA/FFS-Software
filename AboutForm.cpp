#include "AboutForm.h"

AboutForm::AboutForm(QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);
}

AboutForm::~AboutForm()
{
	delete& ui;
}