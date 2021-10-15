#pragma once

#include "EquipmentContext.h";
#include "MeasurementContext.h";

class BindingContext
{
public:
	BindingContext();
	void SetFKEquipment(EquipmentContext* fk_equipment);
	void SetFKMeasurement(MeasurementContext* fk_measurement);

private:
	EquipmentContext* fk_equipment = nullptr;
	MeasurementContext* fk_measurement = nullptr;
};
