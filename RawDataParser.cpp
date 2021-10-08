#include "RawDataParser.h"


#include <QTextStream>
#include <QFile>

RawDataParser::RawDataParser(QString fileLink)
{
	this->fileLink = fileLink;
	this->MPstartFlag = false;
	this->EQstartFlag = false;
}

RawDataParser::RawDataParser()
{
	this->MPstartFlag = false;
	this->EQstartFlag = false;
}

void RawDataParser::SetFileLink(QString fileLink)
{
	this->fileLink = fileLink;
}

void RawDataParser::ParseRawDataFile(DbContext dbContext)
{
	QString header = ReadHeader();
	if (header.contains("Carl Zeiss ConfoCor1"))
	{
		CZConfoCor1Parser(dbContext);
	}
	else if (header.contains("Carl Zeiss ConfoCor2"))
	{
		CZConfoCor2Parser(dbContext);
	}
	else
	{
		SomeOtherDeviceParser(dbContext);
	}
	
}

void RawDataParser::CZConfoCor1Parser(DbContext dbContext)
{

}

void RawDataParser::CZConfoCor2Parser(DbContext dbContext)
{
	QFile file(fileLink);

	if (!file.open(QIODevice::ReadOnly)) 
	{
		qWarning("Cannot open file for reading"); 
	}

	QTextStream in(&file);
	while (!in.atEnd()) 
	{ 
		QString line = in.readLine(); 
		QStringList splittedLine;



		/*if (EQstartFlag == true)
		{

		}
		if (line.contains("BEGIN Lasers"))
		{
			MPstartFlag = false;
			EQstartFlag = true;
		}
		if (MPstartFlag == true)
		{
			splittedLine = line.split('=');
			measurementParameter = new MeasurementParameterContext();
			measurementParameter->SetName(splittedLine[0].trimmed());
			measurementParameter->SetValue(splittedLine[1].trimmed());
			//measurementParameter->SetFKMeasurement();
			measurementParameter->IncrementId();
			dbContext.AddNewMeasurementParameter(*measurementParameter);
		}
		if (line.contains("BEGIN MeasureParameters"))
		{
			MPstartFlag = true;
		}*/
	}

	file.close();
}

void RawDataParser::SomeOtherDeviceParser(DbContext dbContext)
{

}

QString RawDataParser::ReadHeader()
{
	QFile file(fileLink);

	if (!file.open(QIODevice::ReadOnly)) 
	{
		qWarning("Cannot open file for reading"); 
		return 1;
	}

	QTextStream in(&file);
	QString header = in.readLine(); 
	file.close();
	return header;
}