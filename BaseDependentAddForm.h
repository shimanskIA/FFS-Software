#pragma once

#include "BaseAddForm.h"

#include <QtWidgets/QWidget>
#include <QTableView>

class BaseDependentAddForm : public BaseAddForm
{
	Q_OBJECT

public:
	BaseDependentAddForm(QWidget* parent = Q_NULLPTR);

	void SetTableSettings(QTableView* tableView);

protected slots:
	virtual void showAllElementsTable() = 0;
	virtual void chooseElement() = 0;
	virtual void selectChosenElement() = 0;
	virtual void selectElement() = 0;
	virtual void cancelChoose() = 0;
};
