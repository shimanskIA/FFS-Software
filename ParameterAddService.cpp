#include "ParameterAddService.h"
#include "DbWriter.h"

bool ParameterAddService::AddParameterRequestReceiver(QVariant parameter)
{
	bool isRowAdded = DbWriter::GetDbWriterInstance().AddRow(parameter);
	return isRowAdded;
}