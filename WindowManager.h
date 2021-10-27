#pragma once

#include "FFSDatabaseInterface.h"

#include <QString>

class WindowManager
{
public:
	WindowManager();

	void ManageWindows(QString tableName, FFSDatabaseInterface* view, int fk1 = 0, int fk2 = 0);
};
