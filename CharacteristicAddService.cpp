#include "CharacteristicAddService.h"
#include "DbEditor.h"


bool CharacteristicAddService::AddCharacteristicRequestReceiver(CharacteristicsContext* characteristic)
{
	QVariant tableContext;
	tableContext.setValue<CharacteristicsContext*>(characteristic);
	DbEditor* dbEditor = new DbEditor();
	bool isRowAdded = dbEditor->AddRow(tableContext);

	if (isRowAdded)
	{
		characteristic->IncrementId();
		return true;
	}

	return false;
}

Q_DECLARE_METATYPE(CharacteristicsContext*);