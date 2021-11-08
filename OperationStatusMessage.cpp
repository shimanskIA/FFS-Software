#include "OperationStatusMessage.h"

OperationStatusMessage::OperationStatusMessage(bool isSuccessfull)
{
	this->isSuccessfull = isSuccessfull;
}

bool OperationStatusMessage::GetIsSuccessfull()
{
	return isSuccessfull;
}

QString OperationStatusMessage::GetOperationMessage()
{
	return operationMessage;
}

void OperationStatusMessage::SetOperationMessage(QString message)
{
	this->operationMessage = message;
}