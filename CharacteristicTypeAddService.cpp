#include "CharacteristicTypeAddService.h"
#include "DbEditor.h"

bool CharacteristicTypeAddService::AddCharacteristicTypeRequestReceiver(CharacteristicTypeContext* characteristicType)
{
	QVariant tableContext;
	tableContext.setValue<CharacteristicTypeContext*>(characteristicType);
	DbEditor* dbEditor = new DbEditor();
	bool isRowAdded = dbEditor->AddRow(tableContext);

	if (isRowAdded)
	{
		characteristicType->IncrementId();
		return true;
	}

	return false;
}

Q_DECLARE_METATYPE(CharacteristicTypeContext*);