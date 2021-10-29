#include "CharacteristicTypeAddService.h"
#include "TextFileInteractionHelper.h"
#include "NamesHelper.h"
#include "CharacteristicTypeContext.h"
#include "DbEditor.h"

void CharacteristicTypeAddService::AddCharacteristicTypeRequestReceiver(CharacteristicTypeAddForm* view)
{
	QString name = view->GetUI().NameInput->toPlainText();
	QString description = view->GetUI().DescriptionInput->toPlainText();
	CharacteristicTypeContext* characteristicType = new CharacteristicTypeContext(characteristicTypeStatePath);
	characteristicType->SetName(name);
	characteristicType->SetDescription(description);
	QVariant tableContext;
	tableContext.setValue<CharacteristicTypeContext*>(characteristicType);
	DbEditor* dbEditor = new DbEditor();
	bool isRowAdded = dbEditor->AddRow(tableContext);
	view->SetIsRowAdded(isRowAdded);

	if (isRowAdded)
	{
		characteristicType->IncrementId();
	}
}

Q_DECLARE_METATYPE(CharacteristicTypeContext*);