#pragma once

class BindingContext
{
public:
	BindingContext();
	void SetFKEquipment(int fk_equipment);
	void SetFKMeasurement(int fk_measurement);

private:
	int fk_equipment;
	int fk_measurement;
};
