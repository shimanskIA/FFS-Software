#pragma once

#include <QString>
#include <QTableView>

static class TableFillRequestController
{
public:
	static void ManageFillIndependentTableRequest(QString tableName, QTableView* tableView);
};
