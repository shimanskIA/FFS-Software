#pragma once

#include "ui_FFSDatabaseInterface.h"
#include "FFSDatabaseInterface.h"
#include "MeasurementContext.h"
#include "SampleContext.h"
#include "EquipmentContext.h"

#include <QString>
#include <QStandardItemModel>

class FFSDatabaseInterfaceService
{
public:
	static void ImportRequestReceiver(QString fileLink);
	static void ShowMeasurementTableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui);
	static void ShowSampleTableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui);
	static void ShowEquipmentTableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui);
};