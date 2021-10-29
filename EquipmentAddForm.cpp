#include "EquipmentAddForm.h"
#include "EquipmentAddFormController.h"

EquipmentAddForm::EquipmentAddForm(QWidget* parent) : BaseAddForm(parent)
{
	ui.setupUi(this);
	this->setFixedSize(601, 188);
	connect(ui.AddEquipmentButton, SIGNAL(clicked()), this, SLOT(addEquipment()));
}

void EquipmentAddForm::addEquipment()
{
	EquipmentAddFormController::ManageAddEquipmentRequest(this);
	this->close();
}

Ui::EquipmentAddFormClass EquipmentAddForm::GetUI()
{
	return this->ui;
}