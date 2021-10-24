#pragma once

#include <QTableView>
#include <QString>

class DbEditor
{
public:
	DbEditor();
	
	void DeleteRow(QTableView* tableView, QString tableName);
	void UpdateRow(QVariant cellValue, QString tableName, QTableView* tableView);
};
