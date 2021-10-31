#pragma once

#include "ui_FFSDatabaseInterface.h"
#include "FFSDatabaseInterface.h"

#include <QString>
#include <QStandardItemModel>

class FFSDatabaseInterfaceService
{
public:
	static void ImportRequestReceiver(QString fileLink);
	static void DeleteRowRequestReceiver(QString tableName, int selectedId);
	static bool UpdateTableRequestReceiver(QString tableName, QString columnName, QVariant cellValue, int selectedId);
	static bool ReadAbscissaRequestReceiver(int selectedId, QVector<double>& x);
	static bool ReadOrdinateRequestReceiver(int selectedId, QVector<double>& y);
	static void RemoveUnusedIdsRequestReceiver();
};