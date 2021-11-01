#pragma once

#include "ui_EquipmentAddForm.h"
#include "EquipmentAddForm.h"
#include "TableFillRequestController.h"

#include <QString>

static class EquipmentAddFormController : public TableFillRequestController
{
public:
	static void ManageAddEquipmentRequest(EquipmentAddForm* view);
	static void ManageShowAllElementsTableRequest(QTableView* tableView);
	static void ManageChooseUpperElementRequest(EquipmentAddForm* view);
	static void ManageCancelChooseRequest(EquipmentAddForm* view);
	static void ManageChooseExistingEquipmentRequest(EquipmentAddForm* view, int checkboxState);
	static void ManageShowExistingEquipmentRequest(EquipmentAddForm* view);
	static void ManageAddExistingEquipmentRequest(EquipmentAddForm* view, int fk_measuring_system);
};