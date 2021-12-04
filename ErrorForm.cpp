#include "ErrorForm.h"

ErrorForm::ErrorForm(QString errorMessage, QWidget* parent) : QDialog(parent)
{
	ui.setupUi(this);
	this->setFixedSize(571, 271);
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Window);
	ui.errorMessage->setText("ERROR: " + errorMessage);
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
}

void ErrorForm::closeWindow()
{
	this->close();
}