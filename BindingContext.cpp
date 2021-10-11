#include "BindingContext.h"

BindingContext::BindingContext()
{

}

void BindingContext::SetFKEquipment(int fk_equipment)
{
	this->fk_equipment = fk_equipment;
}

void BindingContext::SetFKMeasurement(int fk_measurement)
{
	this->fk_measurement = fk_measurement;
}