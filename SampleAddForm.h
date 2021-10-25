#pragma once

#include <QtWidgets/QWidget>

#include "ui_SampleAddForm.h"
#include "BaseAddForm.h"

class SampleAddForm : public BaseAddForm
{
    Q_OBJECT

public:
    SampleAddForm(QWidget* parent = Q_NULLPTR);

    Ui::SampleAddFormClass GetUI();

private slots:
    void addSample();

private:
    Ui::SampleAddFormClass ui;
};
