#include "DbEditor.h"
#include "DbConnection.h"
#include "TextFileInteractionHelper.h"
#include "EquipmentContext.h"

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

bool DbEditor::AddRow(QVariant tableContext)
{
    if (tableContext.canConvert<EquipmentContext*>())
    {
        return DbConnection::GetDbConnectionInstance().AddEquipmentItem(tableContext.value<EquipmentContext*>());
    }
    else if (tableContext.canConvert<SampleContext*>())
    {
        return DbConnection::GetDbConnectionInstance().AddSample(tableContext.value<SampleContext*>());
    }
    else if (tableContext.canConvert<CharacteristicTypeContext*>())
    {
        return DbConnection::GetDbConnectionInstance().AddCharacteristicType(tableContext.value<CharacteristicTypeContext*>());
    }
    else if (tableContext.canConvert<MeasurementContext*>())
    {
        return DbConnection::GetDbConnectionInstance().AddMeasurement(tableContext.value<MeasurementContext*>());
    }
    else if (tableContext.canConvert<CharacteristicsContext*>())
    {
        return DbConnection::GetDbConnectionInstance().AddCharacteristic(tableContext.value<CharacteristicsContext*>());
    }
    else if (tableContext.canConvert<EquipmentParameterContext*>())
    {
        return DbConnection::GetDbConnectionInstance().AddEquipmentParameter(tableContext.value<EquipmentParameterContext*>());
    }
    else if (tableContext.canConvert<MeasurementParameterContext*>())
    {
        return DbConnection::GetDbConnectionInstance().AddMeasurementParameter(tableContext.value<MeasurementParameterContext*>());
    }
    else if (tableContext.canConvert<MeasuringSystemContext*>())
    {
        return DbConnection::GetDbConnectionInstance().AddForwardMeasuringSystem(tableContext.value<MeasuringSystemContext*>());
    }
    return false;
}

Q_DECLARE_METATYPE(EquipmentContext*);
Q_DECLARE_METATYPE(SampleContext*);
Q_DECLARE_METATYPE(CharacteristicTypeContext*);
Q_DECLARE_METATYPE(MeasurementContext*);
Q_DECLARE_METATYPE(CharacteristicsContext*);
Q_DECLARE_METATYPE(EquipmentParameterContext*);
Q_DECLARE_METATYPE(MeasurementParameterContext*);
Q_DECLARE_METATYPE(MeasuringSystemContext*);