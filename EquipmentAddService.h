#pragma once

#include <QString>
#include "EquipmentContext.h"
#include "BindingContext.h"

class EquipmentAddService
{
public:
	static bool AddEquipmentRequestReceiver(EquipmentContext* equipment);
	static void AddExistingEquipmentRequestReceiver(QList<BindingContext*> bindings, int fk_measuring_system);
};