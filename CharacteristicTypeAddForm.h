#pragma once

#include <QtWidgets/QWidget>

#include "ui_CharacteristicTypeAddForm.h"
#include "BaseAddForm.h"

class CharacteristicTypeAddForm : public BaseAddForm
{
    Q_OBJECT

public:
    CharacteristicTypeAddForm(QWidget* parent = Q_NULLPTR);

    Ui::CharacteristicTypeAddFormClass GetUI();

private slots:
    void manageAddButtonActivity();
    void addCharacteristicType();

private:
    Ui::CharacteristicTypeAddFormClass ui;
};