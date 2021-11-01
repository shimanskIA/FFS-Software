#pragma once

#include <QtWidgets/QWidget>

#include "ui_EquipmentAddForm.h"
#include "BaseDependentAddForm.h"
#include "FFSTableModel.h"

class EquipmentAddForm : public BaseDependentAddForm
{
    Q_OBJECT

public:
    EquipmentAddForm(QWidget* parent = Q_NULLPTR, int fk_measuring_system = 0);

    int GetFKMeasuringSystem();

    bool GetIsFirstTime();
    bool GetIsFirstTimeChecked();
    bool GetIsExistingEquipmentChosen();

    FFSTableModel* GetAllEquipmentTableModel();
    FFSTableModel* GetChosenEquipmentTableModel();

    Ui::EquipmentAddFormClass GetUI();

    void SetIsFirstTime(bool isFirstTime);
    void SetIsFirstTimeChecked(bool isFirstTimeChecked);
    void SetIsExistingEquipmentChosen(bool isExistingEquipmentChosen);

private slots:
    void addEquipment();
    void chooseExistingEquipment(int);
    void sortAllElementsTableRows(int selectedColumn) override;
    void sortChosenElementsTableRows(int selectedColumn) override;
    void showAllElementsTable() override;
    void chooseElement() override;
    void selectChosenElement() override;
    void selectElement() override;
    void cancelChoose() override;

private:
    Ui::EquipmentAddFormClass ui;

    int fk_measuring_system;

    FFSTableModel* allEquipmentTableModel = nullptr;
    FFSTableModel* chosenEquipmentTableModel = nullptr;

    bool isFirstTime = true;
    bool isFirstTimeChecked = true;
    bool isExistingEquipmentChosen = false;
};
