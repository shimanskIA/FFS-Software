#include "BindingContext.h"

BindingContext::BindingContext()
{

}

void BindingContext::SetFKEquipment(EquipmentContext* fk_equipment)
{
	this->fk_equipment = fk_equipment;
}

void BindingContext::SetFKMeasurement(MeasurementContext* fk_measurement)
{
	this->fk_measurement = fk_measurement;
}