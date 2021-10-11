#pragma once

#include <QString>

class TextFileInteractionHelper
{
public:
	static int ReadIdFromTextFile(QString stateFilePath);
	static void WriteIdToTextFile(int id, QString stateFilePath);
	static void DeleteIdFromTextFile(int id, QString idFilePath);
};