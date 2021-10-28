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
};
