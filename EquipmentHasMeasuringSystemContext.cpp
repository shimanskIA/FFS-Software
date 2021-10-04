#include "EquipmentHasMeasuringSystemContext.h"

EquipmentHasMeasuringSystemContext::EquipmentHasMeasuringSystemContext()
{

}

void EquipmentHasMeasuringSystemContext::SetFKEquipment(int fk_equipment)
{
	this->fk_equipment = fk_equipment;
}

void EquipmentHasMeasuringSystemContext::SetFKMeasuringSystem(int fk_measuring_system)
{
	this->fk_measuring_system = fk_measuring_system;
}