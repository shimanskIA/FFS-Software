#pragma once

#include "MeasurementContext.h"

#include <QString>

static class MeasurementAddService
{
public:
	static bool AddMeasurementRequestReceiver(MeasurementContext* measurement);
};
