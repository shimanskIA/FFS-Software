#include "ParameterAddService.h"
#include "DbEditor.h"

bool ParameterAddService::AddParameterRequestReceiver(QVariant parameter)
{
	DbEditor* dbEditor = new DbEditor();
	bool isRowAdded = dbEditor->AddRow(parameter);
	return isRowAdded;
}