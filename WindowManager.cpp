#include "WindowManager.h"
#include "MeasuringSystemAddForm.h"
#include "EquipmentAddForm.h"
#include "SampleAddForm.h"
#include "CharacteristicTypeAddForm.h"
#include "MeasurementAddForm.h"
#include "CharacteristicAddForm.h"
#include "ParameterAddForm.h"

WindowManager::WindowManager()
{

}

void WindowManager::ManageWindows(QString tableName, FFSDatabaseInterface* view, QMap<QString, int> foreignKeys)
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
		MeasurementAddForm* addForm = new MeasurementAddForm(Q_NULLPTR, foreignKeys["measuring system"], foreignKeys["sample"]);
		addForm->show();
		view->SetUpAddView(addForm);
	}
	else if (tableName == "characteristics")
	{
		view->hide();
		CharacteristicAddForm* addForm = new CharacteristicAddForm(Q_NULLPTR, foreignKeys["measurement"], foreignKeys["characteristic type"]);
		addForm->show();
		view->SetUpAddView(addForm);
	}
	else if (tableName == "measurement_parameters")
	{
		view->hide();
		ParameterAddForm* addForm = new ParameterAddForm(Q_NULLPTR, foreignKeys["measurement"], "measurement");
		addForm->show();
		view->SetUpAddView(addForm);
	}
	else if (tableName == "equipment_parameters")
	{
		view->hide();
		ParameterAddForm* addForm = new ParameterAddForm(Q_NULLPTR, foreignKeys["equipment"], "equipment");
		addForm->show();
		view->SetUpAddView(addForm);
	}
}