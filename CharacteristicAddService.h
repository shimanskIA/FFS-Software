#pragma once

#include "ui_CharacteristicAddForm.h"
#include "CharacteristicAddForm.h"

#include <QString>

class CharacteristicAddService
{
public:
	static void AddCharacteristicRequestReceiver(CharacteristicAddForm* view);
};