#include "WindowManager.h"
#include "MeasuringSystemAddForm.h"
#include "EquipmentAddForm.h"
#include "SampleAddForm.h"
#include "CharacteristicTypeAddForm.h"
#include "MeasurementAddForm.h"

WindowManager::WindowManager()
{

}

void WindowManager::ManageWindows(QString tableName, FFSDatabaseInterface* view, int fk1, int fk2)
{
	if (tableName == "measuring_systems")
	{
		view->hide();
		MeasuringSystemAddForm* addForm = new MeasuringSystemAddForm();
		addForm->show();
		view->SetUpAddView(addForm);
	}
	else if (tableName == "equipments")
	{
		view->hide();
		EquipmentAddForm* addForm = new EquipmentAddForm();
		addForm->show();
		view->SetUpAddView(addForm);
	}
	else if (tableName == "samples")
	{
		view->hide();
		SampleAddForm* addForm = new SampleAddForm();
		addForm->show();
		view->SetUpAddView(addForm);
	}
	else if (tableName == "characteristic_types")
	{
		view->hide();
		CharacteristicTypeAddForm* addForm = new CharacteristicTypeAddForm();
		addForm->show();
		view->SetUpAddView(addForm);
	}
	else if (tableName == "measurements")
	{
		view->hide();
		MeasurementAddForm* addForm = new MeasurementAddForm(Q_NULLPTR, fk1, fk2);
		addForm->show();
		view->SetUpAddView(addForm);
	}
}