#pragma once

#include "ui_FFSDatabaseInterface.h"
#include "FFSDatabaseInterface.h"

#include <QString>
#include <QStandardItemModel>

class FFSDatabaseInterfaceService
{
public:
	static void ImportRequestReceiver(QString fileLink);
	static void DeleteRowRequestReceiver(QTableView* tableView, QString tableName);
	static bool UpdateTableRequestReceiver(QVariant cellValue, QString tableName, QTableView* tableView);
	static void RemoveUnusedIdsRequestReceiver();
};