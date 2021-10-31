#pragma once

#include <QStyledItemDelegate>
#include <QString>

class TableItemDelegate : public QStyledItemDelegate
{

    Q_OBJECT

public:
    TableItemDelegate(QObject* parent = 0);
    
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};
