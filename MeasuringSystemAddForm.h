#pragma once

#include <QtWidgets/QWidget>

#include "ui_MeasuringSystemAddForm.h"
#include "FFSTableModel.h"
#include "BaseDependentAddForm.h"

class MeasuringSystemAddForm : public BaseDependentAddForm
{
    Q_OBJECT

public:
    MeasuringSystemAddForm(QWidget* parent = Q_NULLPTR);

    bool GetIsFirstTime();

    Ui::MeasuringSystemAddFormClass GetUI();

    void SetIsFirstTime(bool isFirstTime);

private slots:
    void addMeasuringSystem();
    void showAllElementsTable();
    void chooseElement();
    void selectChosenElement();
    void selectElement();
    void cancelChoose();

private:
    Ui::MeasuringSystemAddFormClass ui;

    bool isFirstTime = true;
};
