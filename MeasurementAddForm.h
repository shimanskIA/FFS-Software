#pragma once

#include <QtWidgets/QWidget>

#include "ui_MeasurementAddForm.h"
#include "FFSTableModel.h"
#include "BaseDependentAddForm.h"

class MeasurementAddForm : public BaseDependentAddForm
{
    Q_OBJECT

public:
    MeasurementAddForm(QWidget* parent = Q_NULLPTR, int fk_measuring_system = 0, int fk_sample = 0);
    ~MeasurementAddForm();

    FFSTableModel* GetAllSamplesTableModel();
    FFSTableModel* GetAllMeasuringSystemsTableModel();
    FFSTableModel* GetChosenSamplesTableModel();
    FFSTableModel* GetChosenMeasuringSystemsTableModel();

    int GetFKMeasuringSystem();
    int GetFKSample();

    bool GetIsFirstTime();

    Ui::MeasurementAddFormClass GetUI();

    void SetIsFirstTime(bool isFirstTime);

    void SetFKMeasuringSystem(int fk_measuring_system);
    void SetFKSample(int fk_sample);

private slots:
    void addMeasurement();
    void showAllElementsTable();
    void chooseElement();
    void selectChosenElement();
    void selectElement();
    void cancelChoose();

private:
    Ui::MeasurementAddFormClass ui;
    FFSTableModel* allSamplesTableModel;
    FFSTableModel* allMeasuringSystemTableModel;
    FFSTableModel* chosenSamplesTableModel;
    FFSTableModel* chosenMeasuringSystemsTableModel;

    int fk_measuring_system = 0;
    int fk_sample = 0;

    bool isFirstTime = true;
};
