#pragma once

#include <QtWidgets/QWidget>

#include "ui_EquipmentAddForm.h"
#include "BaseAddForm.h"

class EquipmentAddForm : public BaseAddForm
{
    Q_OBJECT

public:
    EquipmentAddForm(QWidget* parent = Q_NULLPTR, int fk_measuring_system = 0);

    int GetFKMeasuringSystem();

    Ui::EquipmentAddFormClass GetUI();

private slots:
    void addEquipment();

private:
    Ui::EquipmentAddFormClass ui;
    int fk_measuring_system;
};
