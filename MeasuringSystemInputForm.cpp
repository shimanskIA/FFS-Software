#include "MeasuringSystemInputForm.h"
#include "MeasuringSystemInputFormController.h"

#include <QCloseEvent>

MeasuringSystemInputForm::MeasuringSystemInputForm(QWidget* parent) : QDialog(parent)
{
	ui.setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    ui.continueButton->setDisabled(true);
    connect(ui.continueButton, SIGNAL(clicked()), this, SLOT(proceedNext()));
    connect(ui.NameInput, SIGNAL(textChanged()), this, SLOT(manageContinueButtonActivity()));
    connect(ui.MainContributorInput, SIGNAL(textChanged()), this, SLOT(manageContinueButtonActivity()));
}

Ui::MeasuringSystemInputFormClass MeasuringSystemInputForm::GetUI()
{
    return this->ui;
}

void MeasuringSystemInputForm::proceedNext()
{
    QMap<QString, QString> credentials;
    credentials.insert("name", ui.NameInput->toPlainText());
    credentials.insert("description", ui.DescriptionInput->toPlainText());
    credentials.insert("contributor", ui.MainContributorInput->toPlainText());
    emit measuringSystemSet(credentials);
    this->close();
}

void MeasuringSystemInputForm::manageContinueButtonActivity()
{
    MeasuringSystemInputFormController::ManageContinueButtonActivity(this);
}