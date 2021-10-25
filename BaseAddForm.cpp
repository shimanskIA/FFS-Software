#include "BaseAddForm.h"

#include <QCloseEvent>

BaseAddForm::BaseAddForm(QWidget* parent) : QWidget(parent)
{

}

void BaseAddForm::closeEvent(QCloseEvent* event)
{
    emit windowClosed();
    event->accept();
}

bool BaseAddForm::GetIsRowAdded()
{
	return this->isRowAdded;
}

void BaseAddForm::SetIsRowAdded(bool isRowAdded)
{
	this->isRowAdded = isRowAdded;
}