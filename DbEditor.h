#pragma once

#include "BaseAddForm.h"

#include <QTableView>
#include <QString>

class DbEditor
{
public:
	DbEditor();
	
	void DeleteRow(QTableView* tableView, QString tableName);
	bool UpdateRow(QVariant cellValue, QString tableName, QTableView* tableView);
	bool AddRow(QVariant tableContext);
};
