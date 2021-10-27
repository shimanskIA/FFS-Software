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
	static void ShowMajorTableRequestReceiver(QString tableName, QTableView* tableView);
	static void DeleteRowRequestReceiver(QTableView* tableView, QString tableName);
	static void UpdateTableRequestReceiver(QVariant cellValue, QString tableName, QTableView* tableView);
	static void ShowAddViewRequestReceiver(QString tableName, FFSDatabaseInterface* view, int fk1 = 0, int fk2 = 0);
	static void RemoveUnusedIdsRequestReceiver();
	static void LoadDataToSubtableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui, QTableView* tableView, QString majorTableName, QString minorTableName, int majorTableId);
};