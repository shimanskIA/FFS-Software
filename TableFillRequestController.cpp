#include "TableFillRequestController.h"
#include "TableWriter.h"

void TableFillRequestController::ManageFillIndependentTableRequest(QString tableName, QTableView* tableView)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->RouteMajorRequest(tableName, tableView);
}