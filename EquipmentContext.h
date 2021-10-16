#pragma once

#include <QString>
#include <QList>

#include "TableContext.h"
#include "EquipmentParameterContext.h"

class EquipmentContext : public TableContext
{
public:
	EquipmentContext(QString stateFilePath);
	~EquipmentContext();
	void SetId(int id) override;
	void SetName(QString name);
	void SetDescription(QString description);
	void ChangeEquipmentParametersFK(int new_fk);

	void AddNewEquipmentParameter(EquipmentParameterContext* equipmentParameter);

	QString GetName();
	QString GetDescription();

	QList<EquipmentParameterContext*> GetEquipmentParameters();

	int GetAmountOfEquipmentParameters();

	bool ContainsEquipmentParameter(EquipmentParameterContext* equipmentParameter);

private:
	QString name = "";
	QString description = "";
	
	QList<EquipmentParameterContext*> equipmentParameters;
};
