#pragma once

#include "ui_CharacteristicAddForm.h"
#include "CharacteristicAddForm.h"
#include "TableFillRequestController.h"

#include <QString>

static class CharacteristicAddFormController : public TableFillRequestController
{
public:
	static void ManageAddCharacteristicRequest(CharacteristicAddForm* view);
	static void ManageShowAllElementsTableRequest(QString tableName, QTableView* tableView, CharacteristicAddForm* view, bool load = false);
	static void ManageChooseUpperElementRequest(CharacteristicAddForm* view);
	static void ManageCancelChooseRequest(CharacteristicAddForm* view);
};
