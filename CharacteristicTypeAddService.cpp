#include "CharacteristicTypeAddService.h"
#include "DbWriter.h"

bool CharacteristicTypeAddService::AddCharacteristicTypeRequestReceiver(CharacteristicTypeContext* characteristicType)
{
	QVariant tableContext;
	tableContext.setValue<CharacteristicTypeContext*>(characteristicType);
	bool isRowAdded = DbWriter::GetDbWriterInstance().AddRow(tableContext);

	if (isRowAdded)
	{
		characteristicType->IncrementId();
		return true;
	}

	return false;
}

Q_DECLARE_METATYPE(CharacteristicTypeContext*);