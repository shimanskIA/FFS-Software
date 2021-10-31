#include "CharacteristicAddService.h"
#include "DbWriter.h"


bool CharacteristicAddService::AddCharacteristicRequestReceiver(CharacteristicsContext* characteristic)
{
	QVariant tableContext;
	tableContext.setValue<CharacteristicsContext*>(characteristic);
	DbWriter* dbWriter = new DbWriter();
	bool isRowAdded = dbWriter->AddRow(tableContext);

	if (isRowAdded)
	{
		characteristic->IncrementId();
		return true;
	}

	return false;
}

Q_DECLARE_METATYPE(CharacteristicsContext*);