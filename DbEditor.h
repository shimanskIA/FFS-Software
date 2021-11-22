#pragma once

#include "OperationStatusMessage.h"

#include <QTableView>
#include <QString>

class DbEditor
{
public:
	static DbEditor& GetDbEditorInstance();

	OperationStatusMessage* DeleteFromDatabase(QString tableName, int id);
	OperationStatusMessage* DeleteBindingsWithMeasuringSystem(int fk_measuring_system);
	OperationStatusMessage* UpdateDatabase(QString tableName, QString columnName, QString cellValue, int id);
	
	OperationStatusMessage* UpdateRow(QString tableName, QString columnName, QVariant cellValue, int selectedId);

private:
	DbEditor() {};
	DbEditor(const DbEditor&) {}
};
