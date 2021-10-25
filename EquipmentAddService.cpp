#include "EquipmentAddService.h"
#include "TextFileInteractionHelper.h"
#include "NamesHelper.h"
#include "EquipmentContext.h"
#include "DbEditor.h"

void EquipmentAddService::AddEquipmentRequestReceiver(EquipmentAddForm* view)
{
	QString name = view->GetUI().NameInput->toPlainText();
	QString description = view->GetUI().DescriptionInput->toPlainText();
	EquipmentContext* equipmentItem = new EquipmentContext(equipmentStatePath);
	equipmentItem->SetName(name);
	equipmentItem->SetDescription(description);
	QVariant tableContext;
	tableContext.setValue<EquipmentContext*>(equipmentItem);
	DbEditor* dbEditor = new DbEditor();
	bool isRowAdded = dbEditor->AddRow(tableContext);
	view->SetIsRowAdded(isRowAdded);
	if (isRowAdded)
	{
		equipmentItem->IncrementId();
	}
}

Q_DECLARE_METATYPE(EquipmentContext*);