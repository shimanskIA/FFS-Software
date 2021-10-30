#include "EquipmentAddForm.h"
#include "EquipmentAddFormController.h"

EquipmentAddForm::EquipmentAddForm(QWidget* parent, int fk_measuring_system) : BaseAddForm(parent)
{
	ui.setupUi(this);
	this->setFixedSize(601, 188);
	this->fk_measuring_system = fk_measuring_system;
	connect(ui.AddEquipmentButton, SIGNAL(clicked()), this, SLOT(addEquipment()));
}

void EquipmentAddForm::addEquipment()
{
	EquipmentAddFormController::ManageAddEquipmentRequest(this);
	this->close();
}

int EquipmentAddForm::GetFKMeasuringSystem()
{
	return this->fk_measuring_system;
}

Ui::EquipmentAddFormClass EquipmentAddForm::GetUI()
{
	return this->ui;
}