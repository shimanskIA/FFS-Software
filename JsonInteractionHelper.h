#pragma once

#include <QString>

class JsonInteractionHelper
{
public:
	static int ReadItemFromJsonFile(QString item, QString configFilePath);
	static void EditJsonFile(QString item, int value, QString configFilePath);
};
