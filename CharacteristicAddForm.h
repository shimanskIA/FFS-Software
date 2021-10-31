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
    void showAllElementsTable();
    void chooseElement();
    void selectChosenElement();
    void selectElement();
    void cancelChoose();

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
