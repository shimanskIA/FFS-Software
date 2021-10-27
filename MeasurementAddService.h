#pragma once

#include "ui_MeasurementAddForm.h"
#include "MeasurementAddForm.h"

#include <QString>

class MeasurementAddService
{
public:
	static void ShowAllElementsTableRequestReceiver(QString tableName, QTableView* tableView);
	static void AddMeasurementRequestReceiver(MeasurementAddForm* view);
};
