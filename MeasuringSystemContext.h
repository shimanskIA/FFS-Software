#pragma once

#include "TableContext.h"
#include "BindingContext.h"
#include "MeasurementContext.h"

#include <QString>
#include <QList>

class MeasuringSystemContext : public TableContext
{
public:
	MeasuringSystemContext(QString fileLink);
	~MeasuringSystemContext();

	void SetId(int id) override;
	void SetName(QString name);
	void SetDescription(QString description);
	void SetMainContributorName(QString mainContributorName);

	void AddNewBinding(BindingContext* binding);
	void AddNewMeasurement(MeasurementContext* measurement);

	QString GetName();
	QString GetDescription();
	QString GetMainContributorName();
	QList<MeasurementContext*> GetMeasurements();
	QList<BindingContext*> GetBindings();
	
	int GetAmountOfBindings();

	bool ContainsBindingWithThisEquipment(int equipmentId);

	void ChangeBindingsFK(int new_fk);
	void ChangeMeasurementsFK(int new_fk);

private:
	QString name;
	QString description;
	QString mainContributorName;

	QList<MeasurementContext*> measurements;
	QList<BindingContext*> bindings;
};
