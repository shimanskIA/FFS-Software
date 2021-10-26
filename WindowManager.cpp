#include "WindowManager.h"
#include "MeasuringSystemAddForm.h"
#include "EquipmentAddForm.h"
#include "SampleAddForm.h"
#include "CharacteristicTypeAddForm.h"

WindowManager::WindowManager()
{

}

void WindowManager::ManageWindows(QString tableName, FFSDatabaseInterface* view)
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
}