#include "ErrorForm.h"

ErrorForm::ErrorForm(QString errorMessage, QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);
	this->setStyleSheet("background-color: white;");
	this->setFixedSize(612, 367);
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	ui.errorMessage->setText(errorMessage);
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
}

void ErrorForm::closeWindow()
{
	this->close();
}