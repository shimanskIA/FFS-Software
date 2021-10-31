#include "DbEditor.h"
#include "TextFileInteractionHelper.h"
#include "EquipmentContext.h"

DbEditor::DbEditor()
{
    dbWriter = new DbWriter();
}

void DbEditor::DeleteFromDatabase(QString tableName, int id)
{
    QString sqlRequest = "DELETE FROM %1 WHERE id = %2";
    QSqlQuery query;

    if (!query.exec(sqlRequest.arg(tableName).arg(id)))
    {
        qWarning("Database delete request wasn't proceeded.");
    }
}

bool DbEditor::UpdateDatabase(QString tableName, QString columnName, QString cellValue, int id)
{
    QString sqlUpdateRequest = "UPDATE %1 SET %2 = %3 WHERE id = %4";
    QSqlQuery query;

    if (!query.exec(sqlUpdateRequest.arg(tableName).arg(columnName).arg(cellValue).arg(id)))
    {
        qWarning("Database update request wasn't proceeded.");
        return false;
    }

    return true;
}

bool DbEditor::UpdateRow(QString tableName, QString columnName, QVariant cellValue, int selectedId)
{
    QString dbCellValue;

    if (cellValue.type() == QVariant::Type::String)
    {
        dbCellValue = "'" + cellValue.toString() + "'";
    }
    else
    {
        dbCellValue = cellValue.toString();
    }

    return UpdateDatabase(tableName, columnName, dbCellValue, selectedId);
}