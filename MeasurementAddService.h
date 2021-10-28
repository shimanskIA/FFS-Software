#pragma once

#include "ui_MeasurementAddForm.h"
#include "MeasurementAddForm.h"

#include <QString>

class MeasurementAddService
{
public:
	static void AddMeasurementRequestReceiver(MeasurementAddForm* view);
};
