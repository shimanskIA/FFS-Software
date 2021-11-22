#pragma once

#include "ui_MeasuringSystemAddForm.h"
#include "MeasuringSystemAddForm.h"
#include "TableFillRequestController.h"

#include <QString>

static class MeasuringSystemAddFormController : public TableFillRequestController
{
public:
	static void ManageAddMeasuringSystemRequest(MeasuringSystemAddForm* view);
	static void ManageShowAllElementsTableRequest(QTableView* tableView);
	static void ManageChooseUpperElementRequest(MeasuringSystemAddForm* view);
	static void ManageCancelChooseRequest(MeasuringSystemAddForm* view);
	static void ManageAddButtonActivity(MeasuringSystemAddForm* view);
};
