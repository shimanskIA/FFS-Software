#include "DbEditor.h"
#include "DbConnection.h"

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