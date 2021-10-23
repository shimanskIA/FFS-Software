#pragma once

#include "ui_FFSDatabaseInterface.h"
#include "FFSDatabaseInterface.h"

#include <QString>
#include <QStandardItemModel>

class FFSDatabaseInterfaceService
{
public:
	static void ImportRequestReceiver(QString fileLink);
	static void ShowMeasuringSystemTableRequestReceiver(QTableView* tableView);
	static void ShowCharacteristicsTableRequestReceiver(QTableView* tableView);
	static void ShowMajorTableRequestReceiver(FFSDatabaseInterface* view);
	static void DeleteRowRequestReceiver(QTableView* tableView, QString tableName);
	static void RemoveUnusedIdsRequestReceiver();
	static void LoadDataToSubtableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui, QTableView* tableView, QString majorTableName, QString minorTableName, int majorTableId);
};