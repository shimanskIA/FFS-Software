#pragma once

#include <QString>

class OperationStatusMessage
{
public:
	OperationStatusMessage(bool isSuccessful);

	bool GetIsSuccessfull();
	QString GetOperationMessage();

	void SetOperationMessage(QString message);

private:
	bool isSuccessfull;
	QString operationMessage;
};
