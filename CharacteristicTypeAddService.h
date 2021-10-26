#pragma once

#include "ui_CharacteristicTypeAddForm.h"
#include "CharacteristicTypeAddForm.h"

#include <QString>

class CharacteristicTypeAddService
{
public:
	static void AddCharacteristicTypeRequestReceiver(CharacteristicTypeAddForm* view);
};
