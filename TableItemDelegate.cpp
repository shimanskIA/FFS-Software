#include "TableItemDelegate.h"

#include <QDoubleSpinBox>

TableItemDelegate::TableItemDelegate(QObject* parent) : QStyledItemDelegate(parent)
{

}


QWidget* TableItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QDoubleSpinBox* editor = new QDoubleSpinBox(parent);
    editor->setDecimals(4);
    editor->setFrame(false);
    editor->setMinimum(-1.7976931348623157e308);
    editor->setMaximum(1.7976931348623157e308);
    editor->setSizePolicy(QSizePolicy::Ignored, editor->sizePolicy().verticalPolicy());
    return editor;
}