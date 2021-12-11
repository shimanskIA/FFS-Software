#include "WindowManager.h"
#include "MeasuringSystemAddForm.h"
#include "EquipmentAddForm.h"
#include "SampleAddForm.h"
#include "CharacteristicTypeAddForm.h"
#include "MeasurementAddForm.h"
#include "CharacteristicAddForm.h"
#include "ParameterAddForm.h"
#include "CharacteristicPreviewForm.h"
#include "FFSDatabaseInterfaceService.h"
#include "MeasuringSystemInputForm.h"
#include "OperationStatusMessage.h"
#include "ErrorForm.h"
#include "DbReader.h"

WindowManager& WindowManager::GetWindowManagerInstance()
{
	static WindowManager* windowManagerInstance = 0;

	if (windowManagerInstance == 0)
	{
		windowManagerInstance = new WindowManager();
	}

	return *windowManagerInstance;
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
		EquipmentAddForm* addForm = new EquipmentAddForm(Q_NULLPTR, foreignKeys["measuring system"]);
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

void WindowManager::ShowCharacteristicPreview(QString title, QVector<double> x, QVector<double> y, FFSDatabaseInterface* view, int fk_characteristic)
{
	
	CharacteristicPreviewForm* previewForm = new CharacteristicPreviewForm(title, x, y, fk_characteristic);
	previewForm->show();
	view->AddOpenedCharacteristicPreviewWindow(fk_characteristic, previewForm);
}

void WindowManager::BindMeasuringSystemToInputForm()
{
	MeasuringSystemInputForm* measuringSystemInputForm = new MeasuringSystemInputForm();
	connect(measuringSystemInputForm, &MeasuringSystemInputForm::measuringSystemSet, this, &WindowManager::redirectInitializeMeasuringSystemRequest);
	measuringSystemInputForm->exec();
}

void WindowManager::redirectInitializeMeasuringSystemRequest(QMap<QString, QString> credentials)
{
	OperationStatusMessage* statusMessage = FFSDatabaseInterfaceService::InitializeMeasuringSystemRequestReceiver(credentials);

	if (!statusMessage->GetIsSuccessfull())
	{
		ErrorForm* errorForm = new ErrorForm(statusMessage->GetOperationMessage());
		errorForm->exec();
		BindMeasuringSystemToInputForm();
	}
}