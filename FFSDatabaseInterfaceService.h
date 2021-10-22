#pragma once

#include "ui_FFSDatabaseInterface.h"
#include "FFSDatabaseInterface.h"

#include <QString>
#include <QStandardItemModel>

class FFSDatabaseInterfaceService
{
public:
	static void ImportRequestReceiver(QString fileLink);
	static void ShowMeasurementTableRequestReceiver(QTableView* tableView);
	static void ShowSampleTableRequestReceiver(QTableView* tableView);
	static void ShowEquipmentTableRequestReceiver(QTableView* tableView);
	static void ShowMeasuringSystemTableRequestReceiver(QTableView* tableView);
	static void ShowCharacteristicTypesTableRequestReceiver(QTableView* tableView);
	static void ShowCharacteristicsTableRequestReceiver(QTableView* tableView);
	static void LoadDataToSubtableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui, QTableView* tableView, QString majorTableName, QString minorTableName, int majorTableId);
};