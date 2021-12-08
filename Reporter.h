#pragma once

#include <QString>

class Reporter
{
public:
	static Reporter& GetReporterInstance();

	void Report(QString fileLink);

private:
	Reporter() {};
	Reporter(const Reporter&) {}
};
