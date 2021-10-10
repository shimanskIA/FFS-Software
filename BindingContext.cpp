#include "BindingContext.h"

BindingContext::BindingContext()
{

}

void BindingContext::SetFKEquipment(int fk_equipment)
{
	this->fk_equipment = fk_equipment;
}

void BindingContext::SetFKMeasuringSystem(int fk_measuring_system)
{
	this->fk_measuring_system = fk_measuring_system;
}