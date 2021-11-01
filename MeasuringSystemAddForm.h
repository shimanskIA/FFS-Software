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
    void sortAllElementsTableRows(int selectedColumn) override;
    void sortChosenElementsTableRows(int selectedColumn) override;
    void showAllElementsTable() override;
    void chooseElement() override;
    void selectChosenElement() override;
    void selectElement() override;
    void cancelChoose() override;

private:
    Ui::MeasuringSystemAddFormClass ui;

    bool isFirstTime = true;
};
