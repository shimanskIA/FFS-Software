#pragma once

#include "DbWriter.h"

#include <QTableView>
#include <QString>

class DbEditor
{
public:
	DbEditor();

	void DeleteFromDatabase(QString tableName, int id);
	bool UpdateDatabase(QString tableName, QString columnName, QString cellValue, int id);
	
	bool UpdateRow(QString tableName, QString columnName, QVariant cellValue, int selectedId);

private:
	DbWriter* dbWriter;
};
