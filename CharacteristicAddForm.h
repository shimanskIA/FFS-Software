#pragma once

#pragma once

#include <QtWidgets/QWidget>

#include "ui_CharacteristicAddForm.h"
#include "FFSTableModel.h"
#include "BaseDependentAddForm.h"

class CharacteristicAddForm : public BaseDependentAddForm
{
    Q_OBJECT

public:
    CharacteristicAddForm(QWidget* parent = Q_NULLPTR, int fk_measurement = 0, int fk_characteristic_type = 0);
    ~CharacteristicAddForm();

    FFSTableModel* GetAllMeasurementsTableModel();
    FFSTableModel* GetAllCharacteristicTypesTableModel();
    FFSTableModel* GetChosenMeasurementsTableModel();
    FFSTableModel* GetChosenCharacteristicTypesTableModel();

    int GetFKMeasurement();
    int GetFKCharacteristicType();

    bool GetIsFirstTime();

    Ui::CharacteristicAddFormClass GetUI();

    void SetIsFirstTime(bool isFirstTime);

    void SetFKMeasurement(int fk_measurement);
    void SetFKCharacteristicType(int fk_characteristic_type);

private slots:
    void addCharacteristic();
    void manageAddButtonActivity();
    void sortAllElementsTableRows(int selectedColumn) override;
    void sortChosenElementsTableRows(int selectedColumn) override;
    void showAllElementsTable() override;
    void chooseElement() override;
    void selectChosenElement() override;
    void selectElement() override;
    void cancelChoose() override;

private:
    Ui::CharacteristicAddFormClass ui;
    FFSTableModel* allMeasurementsTableModel;
    FFSTableModel* allCharacteristicTypesTableModel;
    FFSTableModel* chosenMeasurementsTableModel;
    FFSTableModel* chosenCharacteristicTypesTableModel;

    int fk_measurement = 0;
    int fk_characteristic_type = 0;

    bool isFirstTime = true;
};
