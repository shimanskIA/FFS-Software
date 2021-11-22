#pragma once

#include "CharacteristicsContext.h"

#include <QString>

static class CharacteristicAddService
{
public:
	static bool AddCharacteristicRequestReceiver(CharacteristicsContext* characteristic);
};