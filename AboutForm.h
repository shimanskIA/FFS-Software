#pragma once

#include <QtWidgets/QWidget>
#include "ui_AboutForm.h"

class AboutForm : public QWidget
{
    Q_OBJECT

public:
    AboutForm(QWidget* parent = Q_NULLPTR);

private:
    Ui::AboutForm ui;

};
