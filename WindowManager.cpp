#include "WindowManager.h"
#include "MeasuringSystemAddForm.h"
#include "EquipmentAddForm.h"
#include "SampleAddForm.h"

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
}