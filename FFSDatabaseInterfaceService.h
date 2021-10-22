#pragma once

#include "ui_FFSDatabaseInterface.h"
#include "FFSDatabaseInterface.h"

#include <QString>
#include <QStandardItemModel>

class FFSDatabaseInterfaceService
{
public:
	static void ImportRequestReceiver(QString fileLink);
	static void ShowMeasurementTableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui);
	static void ShowSampleTableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui);
	static void ShowEquipmentTableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui);
	static void ShowMeasuringSystemTableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui);
	static void ShowCharacteristicTypesTableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui);
	static void ShowCharacteristicsTableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui);
	static void LoadDataToSubtableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui, QTableView* tableView, QString majorTableName, QString minorTableName, int majorTableId);
};