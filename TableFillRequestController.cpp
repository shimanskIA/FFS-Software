#include "TableFillRequestController.h"
#include "TableWriter.h"

void TableFillRequestController::ManageFillIndependentTableRequest(QString tableName, QTableView* tableView)
{
	TableWriter* tableWriter = new TableWriter();
	tableWriter->RouteMajorRequest(tableName, tableView);
}

void TableFillRequestController::ManageSortRowsRequest(QTableView* tableView, int selectedColumn)
{
    if (tableView->horizontalHeader()->sortIndicatorOrder() == Qt::AscendingOrder)
    {
        tableView->sortByColumn(selectedColumn, Qt::AscendingOrder);
    }
    else
    {
        tableView->sortByColumn(selectedColumn, Qt::DescendingOrder);
    }
}