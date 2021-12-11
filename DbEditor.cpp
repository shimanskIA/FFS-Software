#include "DbEditor.h"

#include <QtSql>

DbEditor& DbEditor::GetDbEditorInstance()
{
    static DbEditor* dbEditorInstance = 0;

    if (dbEditorInstance == 0)
    {
        dbEditorInstance = new DbEditor();
    }

    return *dbEditorInstance;
}

OperationStatusMessage* DbEditor::DeleteFromDatabase(QString tableName, int id)
{
    QString sqlRequest = "DELETE FROM %1 WHERE id = %2";
    QSqlQuery query;

    if (!query.exec(sqlRequest.arg(tableName).arg(id)))
    {
        qWarning("Database delete request wasn't proceeded.");
        OperationStatusMessage* errorStatusMessage = new OperationStatusMessage(false);
        errorStatusMessage->SetOperationMessage("Database delete request wasn't proceeded.");
        return errorStatusMessage;
    }

    return new OperationStatusMessage(true);
}

OperationStatusMessage* DbEditor::DeleteBindingsWithMeasuringSystem(int fk_measuring_system)
{
    QString sqlRequest = "DELETE FROM bindings WHERE fk_measuring_system = %1";
    QSqlQuery query;

    if (!query.exec(sqlRequest.arg(fk_measuring_system)))
    {
        qWarning("Database delete request wasn't proceeded.");
        OperationStatusMessage* errorStatusMessage = new OperationStatusMessage(false);
        errorStatusMessage->SetOperationMessage("Database delete request wasn't proceeded.");
        return errorStatusMessage;
    }

    return new OperationStatusMessage(true);
}

OperationStatusMessage* DbEditor::UpdateDatabase(QString tableName, QString columnName, QString cellValue, int id)
{
    QString sqlUpdateRequest = "UPDATE %1 SET %2 = %3 WHERE id = %4";
    QSqlQuery query;

    if (!query.exec(sqlUpdateRequest.arg(tableName).arg(columnName).arg(cellValue).arg(id)))
    {
        qWarning("Database update request wasn't proceeded.");
        OperationStatusMessage* errorStatusMessage = new OperationStatusMessage(false);
        errorStatusMessage->SetOperationMessage("Database update request wasn't proceeded.");
        return errorStatusMessage;
    }

    return new OperationStatusMessage(true);
}

OperationStatusMessage* DbEditor::UpdateRow(QString tableName, QString columnName, QVariant cellValue, int selectedId)
{
    QString dbCellValue;

    if (cellValue.type() == QVariant::Type::String)
    {
        dbCellValue = "'" + cellValue.toString() + "'";
    }
    else if (cellValue.type() == QVariant::Type::DateTime)
    {
        dbCellValue = cellValue.value<QDateTime>().toString("H:m:s MM/dd/yyyy");
        dbCellValue = "'" + dbCellValue + "'";
    }
    else
    {
        dbCellValue = cellValue.toString();
    }

    return UpdateDatabase(tableName, columnName, dbCellValue, selectedId);
}