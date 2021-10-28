#pragma once

#include "ui_CharacteristicAddForm.h"
#include "CharacteristicAddForm.h"

#include <QString>

class CharacteristicAddFormController
{

public:
	static void ManageAddCharacteristicRequest(CharacteristicAddForm* view);
	static void ManageShowAllElementsTableRequest(QString tableName, QTableView* tableView, CharacteristicAddForm* view, bool load = false);
	static void ManageChooseUpperElementRequest(CharacteristicAddForm* view);
	static void ManageCancelChooseRequest(CharacteristicAddForm* view);
};
