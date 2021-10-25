#pragma once

#include <QtWidgets/QWidget>

#include "ui_EquipmentAddForm.h"
#include "BaseAddForm.h"

class EquipmentAddForm : public BaseAddForm
{
    Q_OBJECT

public:
    EquipmentAddForm(QWidget* parent = Q_NULLPTR);

    Ui::EquipmentAddFormClass GetUI();

private slots:
    void addEquipment();

private:
    Ui::EquipmentAddFormClass ui;

    bool isRowAdded = false;
};
