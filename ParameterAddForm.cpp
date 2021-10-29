#include "ParameterAddForm.h"
#include "ParameterAddFormController.h"

ParameterAddForm::ParameterAddForm(QWidget* parent, int fk, QString majorTable) : BaseAddForm(parent)
{
	ui.setupUi(this);
	FFSTableModel* allMajorElementsTableModel = new FFSTableModel(0, 0);
	FFSTableModel* chosenMajorElementsTableModel = new FFSTableModel(0, 0);
	this->majorTable = majorTable;
	this->fk = fk;
	connect(ui.AddParameterButton, SIGNAL(clicked()), this, SLOT(addParameter()));
}

void ParameterAddForm::addParameter()
{
	ParameterAddFormController::ManageAddParameterRequest(this);
	this->close();
}

int ParameterAddForm::GetFK()
{
	return this->fk;
}

QString ParameterAddForm::GetMajorTableName()
{
	return this->majorTable;
}


void ParameterAddForm::SetFK(int fk)
{
	this->fk = fk;
}

void ParameterAddForm::SetMajorTable(QString majorTable)
{
	this->majorTable = majorTable;
}

Ui::ParameterAddFormClass ParameterAddForm::GetUI()
{
	return this->ui;
}