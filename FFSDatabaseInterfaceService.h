#pragma once

#include "ui_FFSDatabaseInterface.h"
#include "FFSDatabaseInterface.h"
#include "OperationStatusMessage.h"

#include <QString>
#include <QStandardItemModel>

static class FFSDatabaseInterfaceService
{
public:
	static OperationStatusMessage* ImportRequestReceiver(QString fileLink);
	static OperationStatusMessage* DeleteRowRequestReceiver(QString tableName, int selectedId);
	static OperationStatusMessage* UpdateTableRequestReceiver(QString tableName, QString columnName, QVariant cellValue, int selectedId);
	static OperationStatusMessage* ReadAbscissaRequestReceiver(int selectedId, QVector<double>& x);
	static OperationStatusMessage* ReadOrdinateRequestReceiver(int selectedId, QVector<double>& y);
	static OperationStatusMessage* InitializeMeasuringSystemRequestReceiver(QMap<QString, QString> credentials);
	static void ExportRequestReceiver(QString fileLink);
	static void RemoveUnusedIdsRequestReceiver();
};