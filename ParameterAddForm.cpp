#include "ParameterAddForm.h"
#include "ParameterAddFormController.h"

ParameterAddForm::ParameterAddForm(QWidget* parent, int fk, QString majorTable) : BaseAddForm(parent)
{
	ui.setupUi(this);
	ui.AddParameterButton->setDisabled(true);
	this->setFixedSize(462, 207);
	FFSTableModel* allMajorElementsTableModel = new FFSTableModel(0, 0);
	FFSTableModel* chosenMajorElementsTableModel = new FFSTableModel(0, 0);
	this->majorTable = majorTable;
	this->fk = fk;
	connect(ui.AddParameterButton, SIGNAL(clicked()), this, SLOT(addParameter()));
	connect(ui.NameInput, SIGNAL(textChanged()), this, SLOT(manageAddButtonActivity()));
	connect(ui.ValueInput, SIGNAL(textChanged()), this, SLOT(manageAddButtonActivity()));
}

void ParameterAddForm::addParameter()
{
	ParameterAddFormController::ManageAddParameterRequest(this);
	this->close();
}

void ParameterAddForm::manageAddButtonActivity()
{
	ParameterAddFormController::ManageAddButtonActivity(this);
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