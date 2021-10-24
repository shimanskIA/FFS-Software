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