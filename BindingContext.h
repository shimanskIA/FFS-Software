#pragma once

class BindingContext
{
public:
	BindingContext() {};
	void SetFKEquipment(int fk_equipment);
	void SetFKMeasuringSystem(int fk_measuring_system);

	int GetFKEquipment();
	int GetFKMeasuringSystem();

private:
	int fk_equipment = 0;
	int fk_measuring_system = 0;
};
