#include "RawDataParser.h"


#include <QTextStream>
#include <QFile>

RawDataParser::RawDataParser(QString fileLink)
{
	this->fileLink = fileLink;
}

RawDataParser::RawDataParser()
{

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