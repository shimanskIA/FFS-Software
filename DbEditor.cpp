#include "DbEditor.h"
#include "DbConnection.h"
#include "TextFileInteractionHelper.h"

DbEditor::DbEditor()
{

}

void DbEditor::DeleteRow(QTableView* tableView, QString tableName)
{
    int selectedRow = tableView->currentIndex().row();
    QModelIndex indexId = tableView->model()->index(selectedRow, 0);
    int selectedId = tableView->model()->data(indexId).toInt();
    DbConnection::GetDbConnectionInstance().DeleteFromDatabase(tableName, selectedId);
}

void DbEditor::UpdateRow(QVariant cellValue, QString tableName, QTableView* tableView)
{
    int selectedColumn = tableView->currentIndex().column();
    QString columnName = tableView->model()->headerData(selectedColumn, Qt::Horizontal, Qt::DisplayRole).toString();
    columnName = columnName.replace(' ', '_').toLower();
    int selectedRow = tableView->currentIndex().row();
    QModelIndex indexId = tableView->model()->index(selectedRow, 0);
    int selectedId = tableView->model()->data(indexId).toInt();
    QString dbCellValue;

    if (cellValue.type() == QVariant::Type::String)
    {
        dbCellValue = "'" + cellValue.toString() + "'";
    }
    else
    {
        dbCellValue = cellValue.toString();
    }

    DbConnection::GetDbConnectionInstance().UpdateDatabase(tableName, columnName, dbCellValue, selectedId);
}