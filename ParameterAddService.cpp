#include "ParameterAddService.h"
#include "DbWriter.h"

bool ParameterAddService::AddParameterRequestReceiver(QVariant parameter)
{
	DbWriter* dbWriter = new DbWriter();
	bool isRowAdded = dbWriter->AddRow(parameter);
	return isRowAdded;
}