#pragma once

#include "CharacteristicsContext.h"

#include <QString>

class CharacteristicAddService
{
public:
	static bool AddCharacteristicRequestReceiver(CharacteristicsContext* characteristic);
};