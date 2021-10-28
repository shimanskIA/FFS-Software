#pragma once

#include "FFSDatabaseInterface.h"

#include <QString>

class WindowManager
{
public:
	WindowManager();

	void ManageWindows(QString tableName, FFSDatabaseInterface* view, QMap<QString, int> foreignKeys = QMap<QString, int>());
};
