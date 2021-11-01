#pragma once

#include <QString>
#include <QTableView>

static class TableFillRequestController
{
public:
	static void ManageSortRowsRequest(QTableView* tableView, int selectedColumn);

protected:
	static void ManageFillIndependentTableRequest(QString tableName, QTableView* tableView);
};
