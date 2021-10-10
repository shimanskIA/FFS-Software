#include "RawDataParser.h"

#include <QTextStream>
#include <QFile>

RawDataParser::RawDataParser(QString fileLink)
{
	this->fileLink = fileLink;
	this->dataSetNumber = 0;
	this->measurementReadFlag = false;
	this->measureParametersReadFlag = false;
	this->laserParametersReadFlag = false;
	this->pinholeParametersReadFlag = false;
	this->attenuatorPowerParametersReadFlag = false;
	this->detectorParametersReadFlag = false;
	this->attenuatorParametersReadFlag = false;
	this->beamSplitterParametersReadFlag = false;
	this->collimatorParametersReadFlag = false;
	this->sampleCarrierReadFlag = false;
	this->sampleDistributionReadFlag = false;
}

RawDataParser::RawDataParser()
{
	this->dataSetNumber = 0;
	this->measurementReadFlag = false;
	this->measureParametersReadFlag = false;
	this->laserParametersReadFlag = false;
	this->pinholeParametersReadFlag = false;
	this->attenuatorPowerParametersReadFlag = false;
	this->detectorParametersReadFlag = false;
	this->attenuatorParametersReadFlag = false;
	this->beamSplitterParametersReadFlag = false;
	this->collimatorParametersReadFlag = false;
	this->sampleCarrierReadFlag = false;
	this->sampleDistributionReadFlag = false;
}

RawDataParser::~RawDataParser()
{

}

void RawDataParser::SetFileLink(QString fileLink)
{
	this->fileLink = fileLink;
}

void RawDataParser::ParseRawDataFile(DbContext* dbContext)
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

void RawDataParser::CZConfoCor1Parser(DbContext* dbContext)
{

}

void RawDataParser::CZConfoCor2Parser(DbContext* dbContext)
{
	QFile file(fileLink);

	if (!file.open(QIODevice::ReadOnly)) 
	{
		qWarning("Cannot open file for reading"); 
	}

	QTextStream in(&file);

	MeasurementContext* measurement = nullptr;
	SampleContext* sample = nullptr;
	EquipmentContext* equipmentItem = nullptr;
	MeasuringSystemContext* measuringSystem = new MeasuringSystemContext();
	
	QString fullSampleName = "";
	QString fullSampleDistribution = "";
	QString measuringSystemIdentifier = "";

	while (!in.atEnd()) 
	{ 
		QString line = in.readLine(); 
		if (line.contains("BEGIN FcsDataSet" + QString::number(dataSetNumber)))
		{
			if (sample != nullptr)
			{
				sample->SetName(fullSampleName);
				fullSampleName = "";
				dbContext->AddNewSample(sample);
			}
			sample = new SampleContext();
			if (measurement != nullptr)
			{
				dbContext->AddNewMeasurement(measurement);
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
			if (line.contains("NumberChannels"))
			{
				measurement->SetNumberOfChannels(line.split('=').last().trimmed().toInt());
			}
			else if (line.contains("RepeatCount"))
			{
				measurement->SetRepeatCount(line.split('=').last().trimmed().toInt());
			}
			else if (line.contains("KineticsCount"))
			{
				measurement->SetKineticsCount(line.split('=').last().trimmed().toInt());
			}
			else if (line.contains("NumberPositions"))
			{
				measurement->SetNumberPositions(line.split('=').last().trimmed().toInt());
				measurementReadFlag = false;
			}
		}

		else if (line.contains("BEGIN MeasureParameters"))
		{
			measureParametersReadFlag = true;
		}

		else if (measureParametersReadFlag)
		{
			QString parameterName = line.split('=').first().trimmed();
			QString parameterValue = line.split('=').last().trimmed();
			
			if (parameterName.contains("MethodName"))
			{
				measurement->SetName(parameterValue);
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
				parameterName.contains("MeasureTask") ||
				parameterName.contains("MethodComment"))
			{

			}
			else if (parameterName.contains("MeasureSampleComment"))
			{
				sample->SetDescription(parameterValue);
			}
			else
			{
				MeasurementParameterContext *measureParameter = new MeasurementParameterContext();
				measureParameter->SetName(parameterName);
				measureParameter->SetValue(parameterValue);
				measureParameter->SetFKMeasurement(measurement->GetId());
				dbContext->AddNewMeasurementParameter(measureParameter);

				if (line.contains("SizePdHistogram"))
				{
					measureParametersReadFlag = false;
				}
			}
		}

		else if (line.contains("BEGIN Laser") && !line.contains("Lasers"))
		{
			CreateNewEquipmentItem("Laser", laserParametersReadFlag, equipmentItem);
			Bind(measuringSystem, equipmentItem, dbContext);
		}

		else if (laserParametersReadFlag)
		{
			CascadeEquipmentParametersRead(line, laserParametersReadFlag, "LaserInUse", equipmentItem, dbContext);
		}

		else if (line.contains("BEGIN PinholeDiameter") && !line.contains("PinholeDiameters"))
		{
			CreateNewEquipmentItem("PinholeDiameter", pinholeParametersReadFlag, equipmentItem);
			Bind(measuringSystem, equipmentItem, dbContext);
		}

		else if (pinholeParametersReadFlag)
		{
			CascadeEquipmentParametersRead(line, pinholeParametersReadFlag, "DetectorPinholeDiameter", equipmentItem, dbContext);
		}

		else if (line.contains("BEGIN AttenuatorPower") && !line.contains("AttenuatorPowers"))
		{
			CreateNewEquipmentItem("AttenuatorPower", attenuatorPowerParametersReadFlag, equipmentItem);
			Bind(measuringSystem, equipmentItem, dbContext);
		}

		else if (attenuatorPowerParametersReadFlag)
		{
			CascadeEquipmentParametersRead(line, attenuatorPowerParametersReadFlag, "AttenuatorInUse", equipmentItem, dbContext);
		}

		else if (line.contains("BEGIN Detector") && !line.contains("Detectors"))
		{
			CreateNewEquipmentItem("Detector", detectorParametersReadFlag, equipmentItem);
			Bind(measuringSystem, equipmentItem, dbContext);
		}

		else if (detectorParametersReadFlag)
		{
			if (line.contains("DetectorName"))
			{
				QString sampleName = line.split('=').last().trimmed();
				if (fullSampleName.isEmpty())
				{
					fullSampleName += sampleName;
				}
				else
				{
					fullSampleName += "/";
					fullSampleName += sampleName;
				}
			}
			CascadeEquipmentParametersRead(line, detectorParametersReadFlag, "DetectorFilterName", equipmentItem, dbContext);
		}

		else if (line.contains("BEGIN Attenuator ") && !line.contains("Attenuators"))
		{
			CreateNewEquipmentItem("Attenuator", attenuatorParametersReadFlag, equipmentItem);
			Bind(measuringSystem, equipmentItem, dbContext);
		}

		else if (attenuatorParametersReadFlag)
		{
			CascadeEquipmentParametersRead(line, attenuatorParametersReadFlag, "AttenuatorInUse", equipmentItem, dbContext);
		}

		else if (line.contains("BEGIN BeamSplitter") && !line.contains("BeamSplitters"))
		{
			CreateNewEquipmentItem("BeamSplitter", beamSplitterParametersReadFlag, equipmentItem);
			Bind(measuringSystem, equipmentItem, dbContext);
		}

		else if (beamSplitterParametersReadFlag)
		{
			CascadeEquipmentParametersRead(line, beamSplitterParametersReadFlag, "BeamSplitterFilterName", equipmentItem, dbContext);
		}

		else if (line.contains("BEGIN Collimator") && !line.contains("Collimators"))
		{
			CreateNewEquipmentItem("Collimator", collimatorParametersReadFlag, equipmentItem);
			Bind(measuringSystem, equipmentItem, dbContext);
		}

		else if (collimatorParametersReadFlag)
		{
			CascadeEquipmentParametersRead(line, collimatorParametersReadFlag, "CollimatorPosition", equipmentItem, dbContext);
		}

		else if (line.contains("BEGIN SampleCarrier"))
		{
			CreateNewEquipmentItem("SampleCarrier", sampleCarrierReadFlag, equipmentItem);
			Bind(measuringSystem, equipmentItem, dbContext);
		}

		else if (sampleCarrierReadFlag)
		{
			if (line.contains("SampleDistribution"))
			{
				QString sampleDistributionFirstElement = line.split('=').last().trimmed();
				fullSampleDistribution += sampleDistributionFirstElement;
				sampleDistributionReadFlag = true;
			}
			else if(sampleDistributionReadFlag)
			{
				if (line.contains("SamplePositions") && !line.contains("Usage"))
				{
					sampleDistributionReadFlag = false;
					EquipmentParameterContext* equipmentParameter = new EquipmentParameterContext();
					equipmentParameter->SetName("SampleDistribution");
					equipmentParameter->SetValue(fullSampleDistribution);
					equipmentParameter->SetFKEquipment(equipmentItem->GetId());
					dbContext->AddNewEquipmentParameter(equipmentParameter);
				}
				else
				{
					QString sampleDistributionElement = line.trimmed();
					fullSampleDistribution += " ";
					fullSampleDistribution += sampleDistributionElement;
				}
			}
			
			if (!sampleDistributionReadFlag)
			{
				CascadeEquipmentParametersRead(line, sampleCarrierReadFlag, "SamplePositionsUsage", equipmentItem, dbContext);
			}
		}
	}

	dbContext->AddNewMeasurement(measurement);
	sample->SetName(fullSampleName);
	dbContext->AddNewSample(sample);

	file.close();
}

void RawDataParser::SomeOtherDeviceParser(DbContext* dbContext)
{

}

void RawDataParser::CascadeEquipmentParametersRead(QString line, bool& flag, QString endLine, EquipmentContext*& equipmentItem, DbContext* dbContext)
{
	QString parameterName = line.split('=').first().trimmed();
	QString parameterValue = line.split('=').last().trimmed();
	EquipmentParameterContext* equipmentParameter = new EquipmentParameterContext();
	equipmentParameter->SetName(parameterName);
	equipmentParameter->SetValue(parameterValue);
	equipmentParameter->SetFKEquipment(equipmentItem->GetId());
	dbContext->AddNewEquipmentParameter(equipmentParameter);

	if (line.contains(endLine))
	{
		dbContext->AddNewEquipment(equipmentItem);
		flag = false;
	}
}

void RawDataParser::CreateNewEquipmentItem(QString name, bool& flag, EquipmentContext*& equipmentItem)
{
	QString description = "Write your description here.";
	equipmentItem = new EquipmentContext();
	equipmentItem->SetName(name);
	equipmentItem->SetDescription(description);
	flag = true;
}

void RawDataParser::Bind(MeasuringSystemContext* measuringSystem, EquipmentContext*& equipmentItem, DbContext* dbContext)
{
	BindingContext* binding = new BindingContext();
	binding->SetFKMeasuringSystem(measuringSystem->GetId());
	binding->SetFKEquipment(equipmentItem->GetId());
	dbContext->AddNewBinding(binding);
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