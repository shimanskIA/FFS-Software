#pragma once

#include "MeasurementContext.h"

#include <QString>

class MeasurementAddService
{
public:
	static bool AddMeasurementRequestReceiver(MeasurementContext* measurement);
};
