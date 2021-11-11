#pragma once

#include <QStandardItemModel>
#include <QString>

class FFSTableModel : public QStandardItemModel
{
public:
	FFSTableModel(int row, int column);

	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

	QList<QVariant> getColumnItemsThatContainValue(int column, QString value);
};
