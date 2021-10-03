#include "RawDataParser.h"

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
	QString parsingType = FindParsingType();
	if (parsingType == "Carl Zeiss ConfoCor1")
	{
		CZConfoCor1Parser(dbContext);
	}
	else if (parsingType == "Carl Zeiss ConfoCor2")
	{
		CZConfoCor2Parser(dbContext);
	}
	
}

void RawDataParser::CZConfoCor1Parser(DbContext dbContext)
{

}

void RawDataParser::CZConfoCor2Parser(DbContext dbContext)
{

}

QString RawDataParser::FindParsingType()
{
	return "sum string";
}