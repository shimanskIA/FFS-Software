#include "FFSTableModel.h"

FFSTableModel::FFSTableModel(int row, int column) : QStandardItemModel(row, column)
{

}

bool FFSTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	QStandardItemModel::setData(index, value, role);
	emit dataChanged(index, index);
	return true;
}

QList<QVariant> FFSTableModel::getColumnItemsThatContainValue(int column, QString value)
{
	QList<QVariant> columnCells;

	for (int i = 0; i < this->rowCount(); i++)
	{
		QVariant cellValue = this->data(this->index(i, column));

		if (cellValue.toString() == value || cellValue.toString().contains(value + " ("))
		{
			columnCells.append(this->data(this->index(i, column)));
		}
	}

	return columnCells;
}