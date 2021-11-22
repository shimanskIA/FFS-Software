#include "BindingContext.h"

void BindingContext::SetFKEquipment(int fk_equipment)
{
	this->fk_equipment = fk_equipment;
}

void BindingContext::SetFKMeasuringSystem(int fk_measurement)
{
	this->fk_measuring_system = fk_measurement;
}

int BindingContext::GetFKEquipment()
{
	return this->fk_equipment;
}

int BindingContext::GetFKMeasuringSystem()
{
	return this->fk_measuring_system;
}