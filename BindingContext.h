#pragma once

class BindingContext
{
public:
	BindingContext();
	void SetFKEquipment(int fk_equipment);
	void SetFKMeasuringSystem(int fk_measuring_system);

private:
	int fk_equipment;
	int fk_measuring_system;
};
