#pragma once

#include "ui_MeasurementAddForm.h"
#include "MeasurementAddForm.h"
#include "TableFillRequestController.h"

#include <QString>

static class MeasurementAddFormController : TableFillRequestController
{
public:
	static void ManageAddMeasurementRequest(MeasurementAddForm* view);
	static void ManageShowAllElementsTableRequest(QString tableName, QTableView* tableView, MeasurementAddForm* view, bool load = false);
	static void ManageChooseUpperElementRequest(MeasurementAddForm* view);
	static void ManageCancelChooseRequest(MeasurementAddForm* view);
};
