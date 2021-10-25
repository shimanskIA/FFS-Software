#pragma once

#include <QtWidgets/QWidget>

#include "ui_MeasuringSystemAddForm.h"
#include "BaseAddForm.h"

class MeasuringSystemAddForm : public BaseAddForm
{
    Q_OBJECT

public:
    MeasuringSystemAddForm(QWidget* parent = Q_NULLPTR);

private slots:
    void addMeasuringSystem();

private:
    Ui::MeasuringSystemAddFormClass ui;
};
