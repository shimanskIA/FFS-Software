#include "AboutForm.h"

AboutForm::AboutForm(QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);
}

AboutForm& AboutForm::GetAboutFormInstance()
{
	static AboutForm* aboutFormInstance = 0;

	if (aboutFormInstance == 0)
	{
		aboutFormInstance = new AboutForm();
	}

	return *aboutFormInstance;
}
