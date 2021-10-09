#include "RawDataParser.h"

#include <QTextStream>
#include <QFile>

RawDataParser::RawDataParser(QString fileLink)
{
	this->fileLink = fileLink;
	this->dataSetNumber = 0;
	this->measurementReadFlag = false;
	this->measureParametersReadFlag = false;
}

RawDataParser::RawDataParser()
{
	this->dataSetNumber = 0;
	this->measurementReadFlag = false;
	this->measureParametersReadFlag = false;
}

RawDataParser::~RawDataParser()
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

	MeasurementContext* measurement = nullptr;
	SampleContext* sample = nullptr;
	MeasuringSystemContext* measuringSystem = new MeasuringSystemContext();

	QStringList* samples = new QStringList();

	while (!in.atEnd()) 
	{ 
		QString line = in.readLine(); 
		if (line.contains("BEGIN FcsDataSet" + QString::number(dataSetNumber)))
		{
			if (sample != nullptr)
			{
				dbContext.AddNewSample(sample);
			}
			sample = new SampleContext();
			if (measurement != nullptr)
			{
				dbContext.AddNewMeasurement(measurement);
			}
			measurement = new MeasurementContext();
			measurement->SetFileLink(fileLink);
			measurement->SetFKMeasuringSystem(measuringSystem->GetId());
			measurement->SetFKSample(sample->GetId());
			measurementReadFlag = true;
			dataSetNumber++;
		}

		else if (measurementReadFlag)
		{
			QStringList splittedLine;
			if (line.contains("NumberChannels"))
			{
				splittedLine = line.split('=');
				measurement->SetNumberOfChannels(splittedLine.last().trimmed().toInt());
			}
			else if (line.contains("RepeatCount"))
			{
				splittedLine = line.split('=');
				measurement->SetRepeatCount(splittedLine.last().trimmed().toInt());
			}
			else if (line.contains("KineticsCount"))
			{
				splittedLine = line.split('=');
				measurement->SetKineticsCount(splittedLine.last().trimmed().toInt());
			}
			else if (line.contains("NumberPositions"))
			{
				splittedLine = line.split('=');
				measurement->SetNumberPositions(splittedLine.last().trimmed().toInt());
				measurementReadFlag = false;
			}
		}

		else if (line.contains("BEGIN MeasureParameters"))
		{
			measureParametersReadFlag = true;
		}

		else if (measureParametersReadFlag)
		{
			QStringList splittedLine = line.split('=');
			QString parameterName = splittedLine.first().trimmed();
			QString parameterValue = splittedLine.last().trimmed();
			
			if (parameterName.contains("MethodName"))
			{
				measurement->SetName(parameterValue);

				for (int i = 0; i < sampleTypes->length(); i++)
				{
					if (parameterValue.contains(sampleTypes[i]))
					{
						samples->append(sampleTypes[i]);
					}
				}
			}
			else if (parameterName.contains("MeasureDate"))
			{
				measurement->SetDateTime(parameterValue);
			}
			else if (
				parameterName.contains("MethodDate") || 
				parameterName.contains("User") ||
				parameterName.contains("MethodCategory") ||
				parameterName.contains("Auto") ||
				parameterName.contains("MethodStatus") ||
				parameterName.contains("MeasureTask"))
			{

			}
			else if (parameterName.contains("MeasureSampleComment"))
			{
				sample->SetDescription(parameterValue);

				for (int i = 0; i < sampleTypes->length(); i++)
				{
					if (parameterValue.contains(sampleTypes[i]))
					{
						samples->append(sampleTypes[i]);
					}
				}
			}
			else if (line.contains("MethodComment"))
			{

				for (int i = 0; i < sampleTypes->length(); i++)
				{
					if (parameterValue.contains(sampleTypes[i]))
					{
						samples->append(sampleTypes[i]);
					}
				}
			}
			else
			{
				MeasurementParameterContext *measureParameter = new MeasurementParameterContext();
				measureParameter->SetName(parameterName);
				measureParameter->SetValue(parameterValue);
				measureParameter->SetFKMeasurement(measurement->GetId());
				dbContext.AddNewMeasurementParameter(measureParameter);
				if (line.contains("SizePdHistogram"))
				{
					QString fullSampleName = "";
					for (int i = 0; i < samples->length(); i++)
					{
						if (i == 0)
						{
							fullSampleName += samples->at(i);
						}
						else
						{
							fullSampleName += "/";
							fullSampleName += samples->at(i);
						}
					}
					sample->SetName(fullSampleName);
					measureParametersReadFlag = false;
				}
			}
		}

		else if (line.contains("BEGIN Lasers"))
		{
			
		}
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