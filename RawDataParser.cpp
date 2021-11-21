#include "RawDataParser.h"
#include "NamesHelper.h"
#include "MeasuringSystemInputForm.h"

#include <QTextStream>
#include <QFile>

RawDataParser::RawDataParser(QString fileLink)
{
	this->fileLink = fileLink;
	this->measuringSystem = new MeasuringSystemContext(measuringSystemStatePath);
	this->measuringSystem->SetDescription("Write your description here.");
}

RawDataParser::RawDataParser()
{

}

RawDataParser::~RawDataParser()
{

}

void RawDataParser::SetFileLink(QString fileLink)
{
	this->fileLink = fileLink;
}

OperationStatusMessage* RawDataParser::ParseRawDataFile(DbContext* dbContext)
{
	QString header = ReadHeader();

	if (header.contains("Carl Zeiss ConfoCor1"))
	{
		return CZConfoCor1Parser(dbContext);
	}
	else if (header.contains("Carl Zeiss ConfoCor2"))
	{
		return CZConfoCor2Parser(dbContext);
	}
	else if (header.contains("Some other device"))
	{
		return SomeOtherDeviceParser(dbContext);
	}

	OperationStatusMessage* errorStatusMessage = new OperationStatusMessage(false);
	errorStatusMessage->SetOperationMessage("There's no parser found for chosen file.");
	return errorStatusMessage;
}

OperationStatusMessage* RawDataParser::CZConfoCor1Parser(DbContext* dbContext)
{
	return new OperationStatusMessage(true);
}

OperationStatusMessage* RawDataParser::CZConfoCor2Parser(DbContext* dbContext)
{
	QFile file(fileLink);

	if (!file.open(QIODevice::ReadOnly)) 
	{
		qWarning("Cannot open file for reading"); 
		OperationStatusMessage* errorStatusMessage = new OperationStatusMessage(false);
		errorStatusMessage->SetOperationMessage("It was unable to open this file for reading.");
		return errorStatusMessage;
	}

	QTextStream in(&file);

	MeasurementContext* measurement = nullptr;
	SampleContext* sample = nullptr;
	EquipmentContext* equipmentItem = nullptr;
	CharacteristicsContext* characteristic = nullptr;

	MeasuringSystemInputForm* measuringSystemInputForm = new MeasuringSystemInputForm();
	connect(measuringSystemInputForm, &MeasuringSystemInputForm::measuringSystemSet, this, &RawDataParser::createMeasuringSystem);
	measuringSystemInputForm->exec();

	QMap<QString, CharacteristicTypeContext*> usedCharacteristicTypes;
	QString fullSampleName = "";
	QString fullSampleDistribution = "";
	QString actualChannelName = "";

	double firstTimeGap;
	double secondTimeGap;

	int numberOfIterations;
	int actualIteration = 1;

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

			sample = new SampleContext(sampleStatePath);
			
			if (measurement != nullptr)
			{
				measurement->SetFKMeasuringSystem(measuringSystem->GetId());
				measuringSystem->AddNewMeasurement(measurement);
				firstDataSetReadFlag = false;
			}

			measurement = new MeasurementContext(measurementStatePath);
			measurement->SetFileLink(fileLink);
			measurement->SetFKSample(sample);
			measurementReadFlag = true;
			dataSetNumber++;
		}

		else if (measurementReadFlag)
		{
			try
			{
				bool wasConverted;

				if (line.contains("NumberChannels"))
				{
					measurement->SetNumberOfChannels(line.split('=').last().trimmed().toInt(&wasConverted));

					if (!wasConverted)
					{
						QString ex = "Number of channels seems to have an invalid value";
						throw (ex);
					}
				}
				else if (line.contains("RepeatCount"))
				{
					measurement->SetRepeatCount(line.split('=').last().trimmed().toUInt(&wasConverted));

					if (!wasConverted)
					{
						QString ex = "Repeat count seems to have an invalid value";
						throw (ex);
					}
				}
				else if (line.contains("KineticsCount"))
				{
					measurement->SetKineticsCount(line.split('=').last().trimmed().toUInt());

					if (!wasConverted)
					{
						QString ex = "Kinetics count seems to have an invalid value";
						throw (ex);
					}
				}
				else if (line.contains("NumberPositions"))
				{
					measurement->SetNumberPositions(line.split('=').last().trimmed().toUInt());

					if (!wasConverted)
					{
						QString ex = "Number positions seems to have an invalid value.";
						throw (ex);
					}

					measurementReadFlag = false;
				}
			}
			catch (QString ex)
			{
				OperationStatusMessage* errorStatusMessage = new OperationStatusMessage(false);
				errorStatusMessage->SetOperationMessage(ex);
				return errorStatusMessage;
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
				MeasurementParameterContext *measureParameter = new MeasurementParameterContext(measurementParametersStatePath);
				measureParameter->SetName(parameterName);
				measureParameter->SetValue(parameterValue);
				measureParameter->SetFKMeasurement(measurement->GetId());
				measurement->AddNewMeasurementParameter(measureParameter);

				if (line.contains("SizePdHistogram"))
				{
					measureParametersReadFlag = false;
				}
			}
		}

		if (line.contains("BEGIN Laser") && !line.contains("Lasers") && firstDataSetReadFlag)
		{
			CreateNewEquipmentItem("Laser", laserParametersReadFlag, equipmentItem);
			Bind(measuringSystem, equipmentItem, dbContext);
		}

		else if (laserParametersReadFlag)
		{
			CascadeEquipmentParametersRead(line, laserParametersReadFlag, "LaserPower", equipmentItem, dbContext);
		}

		else if (line.contains("BEGIN PinholeDiameter") && !line.contains("PinholeDiameters") && firstDataSetReadFlag)
		{
			CreateNewEquipmentItem("PinholeDiameter", pinholeParametersReadFlag, equipmentItem);
			Bind(measuringSystem, equipmentItem, dbContext);
		}

		else if (pinholeParametersReadFlag)
		{
			CascadeEquipmentParametersRead(line, pinholeParametersReadFlag, "DetectorPinholeName", equipmentItem, dbContext);
		}

		else if (line.contains("BEGIN AttenuatorPower") && !line.contains("AttenuatorPowers") && firstDataSetReadFlag)
		{
			CreateNewEquipmentItem("AttenuatorPower", attenuatorPowerParametersReadFlag, equipmentItem);
			Bind(measuringSystem, equipmentItem, dbContext);
		}

		else if (attenuatorPowerParametersReadFlag)
		{
			CascadeEquipmentParametersRead(line, attenuatorPowerParametersReadFlag, "AttenuatorWavelength", equipmentItem, dbContext);
		}

		else if (line.contains("DetectorName"))
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

		else if (line.contains("BEGIN Attenuator ") && !line.contains("Attenuators") && firstDataSetReadFlag)
		{
			CreateNewEquipmentItem("Attenuator", attenuatorParametersReadFlag, equipmentItem);
			Bind(measuringSystem, equipmentItem, dbContext);
		}

		else if (attenuatorParametersReadFlag)
		{
			CascadeEquipmentParametersRead(line, attenuatorParametersReadFlag, "AttenuatorWavelength", equipmentItem, dbContext);
		}

		else if (line.contains("BEGIN BeamSplitter") && !line.contains("BeamSplitters") && firstDataSetReadFlag)
		{
			CreateNewEquipmentItem("BeamSplitter", beamSplitterParametersReadFlag, equipmentItem);
			Bind(measuringSystem, equipmentItem, dbContext);
		}

		else if (beamSplitterParametersReadFlag)
		{
			CascadeEquipmentParametersRead(line, beamSplitterParametersReadFlag, "BeamSplitterFilterSet", equipmentItem, dbContext);
		}

		else if (line.contains("BEGIN Collimator") && !line.contains("Collimators") && firstDataSetReadFlag)
		{
			CreateNewEquipmentItem("Collimator", collimatorParametersReadFlag, equipmentItem);
			Bind(measuringSystem, equipmentItem, dbContext);
		}

		else if (collimatorParametersReadFlag)
		{
			CascadeEquipmentParametersRead(line, collimatorParametersReadFlag, "CollimatorName", equipmentItem, dbContext);
		}

		else if (line.contains("BEGIN Channel") && !line.contains("Channel "))
		{
			characteristic = new CharacteristicsContext(characteristicStatePath);
			actualChannelName = line.trimmed().split(' ').at(1);
			channelNumber++;
		}

		else if (line.contains("BEGIN Correlation") && !line.contains("Correlation "))
		{
			characteristic = new CharacteristicsContext(characteristicStatePath);
			actualChannelName = line.trimmed().split(' ').at(1);
			correlationNumber++;
		}

		else if (line.contains("ArrayUsage") || line.contains("ArrayUasge"))
		{
			QString actualCharacteristicType = line.split('=').first().trimmed();

			if (line.contains("ArrayUsage"))
			{
				actualCharacteristicType = actualCharacteristicType.split("ArrayUsage").first().trimmed();
			}
			else
			{
				actualCharacteristicType = actualCharacteristicType.split("ArrayUasge").first().trimmed();
			}

			if (!usedCharacteristicTypes.contains(actualCharacteristicType))
			{
				CharacteristicTypeContext* characteristicType = new CharacteristicTypeContext(characteristicTypeStatePath);
				characteristicType->SetName(actualCharacteristicType);
				characteristicType->SetDescription("Write your description here.");
				usedCharacteristicTypes.insert(actualCharacteristicType, characteristicType);
				dbContext->AddNewCharacteristicType(characteristicType);
			}

			if (characteristic == nullptr)
			{
				characteristic = new CharacteristicsContext(characteristicStatePath);
			}
			
			numberOfPointsReadFlag = true;
			QString characteristicName = (measurement->GetName() + measurement->GetFileLink().split('/').last() + measurement->GetDateTime()).toUpper();
			characteristic->SetChannel(actualChannelName);
			characteristic->SetFKCharacteristicType(usedCharacteristicTypes[actualCharacteristicType]);
			characteristic->SetFKMeasurement(measurement->GetId());
			characteristic->SetName(characteristicName);
		}

		else if(numberOfPointsReadFlag)
		{
			QString numberOfRowsAndColumns = line.split('=').last().trimmed();

			try
			{
				bool wasConverted;
				uint numberOfPoints = numberOfRowsAndColumns.split(' ').first().toUInt(&wasConverted);

				if (!wasConverted)
				{
					QString ex = "Invalid number of points.";
					throw (ex);
				}

				numberOfPointsReadFlag = false;
				characteristicReadFlag = true;
				characteristic->SetNumberOfPoints(numberOfPoints);
				numberOfIterations = numberOfPoints;
			}
			catch (QString ex)
			{
				OperationStatusMessage* errorStatusMessage = new OperationStatusMessage(false);
				errorStatusMessage->SetOperationMessage(ex);
				return errorStatusMessage;
			}
		}

		else if (characteristicReadFlag)
		{
			QStringList coordinates = GetCoordinates(line);
			QString x = coordinates.first();
			QString y = coordinates.last();

			try
			{
				bool wasXConverted;
				bool wasYConverted;
				x.toDouble(&wasXConverted);
				y.toDouble(&wasYConverted);

				if (!wasXConverted || !wasYConverted)
				{
					QString ex = "X or Y coordinates have invalid values.";
					throw (ex);
				}
			}
			catch (QString ex)
			{
				OperationStatusMessage* errorStatusMessage = new OperationStatusMessage(false);
				errorStatusMessage->SetOperationMessage(ex);
				return errorStatusMessage;
			}

			characteristic->AddNewXCoordinate(x);
			characteristic->AddNewYCoordinate(y);

			if (actualIteration == 1)
			{
				firstTimeGap = x.toDouble();
				actualIteration++;
			}
			else if (actualIteration == 2)
			{
				secondTimeGap = x.toDouble();
				actualIteration++;
			}
			else if (actualIteration == numberOfIterations)
			{
				characteristicReadFlag = false;
				characteristic->SetBinTime(secondTimeGap - firstTimeGap);
				measurement->AddNewCharacteristicsSet(characteristic);
				characteristic = nullptr;
				actualIteration = 1;
			}
			else
			{
				actualIteration++;
			}
		}
	}

	measurement->SetFKMeasuringSystem(measuringSystem->GetId());
	measuringSystem->AddNewMeasurement(measurement);
	sample->SetName(fullSampleName);
	dbContext->AddNewSample(sample);
	dbContext->SetMeasuringSystem(measuringSystem);

	file.close();
}

OperationStatusMessage* RawDataParser::SomeOtherDeviceParser(DbContext* dbContext)
{
	return new OperationStatusMessage(true);
}

void RawDataParser::CascadeEquipmentParametersRead(QString line, bool& flag, QString endLine, EquipmentContext*& equipmentItem, DbContext* dbContext)
{
	QString parameterName = line.split('=').first().trimmed();
	QString parameterValue = line.split('=').last().trimmed();
	EquipmentParameterContext* equipmentParameter = new EquipmentParameterContext(equipmentParameterStatePath);
	equipmentParameter->SetName(parameterName);
	equipmentParameter->SetValue(parameterValue);
	equipmentParameter->SetFKEquipment(equipmentItem->GetId());
	equipmentItem->AddNewEquipmentParameter(equipmentParameter);

	if (line.contains(endLine))
	{
		dbContext->AddNewEquipment(equipmentItem);
		flag = false;
	}
}

void RawDataParser::CreateNewEquipmentItem(QString name, bool& flag, EquipmentContext*& equipmentItem)
{
	QString description = "Write your description here.";
	equipmentItem = new EquipmentContext(equipmentStatePath);
	equipmentItem->SetName(name);
	equipmentItem->SetDescription(description);
	flag = true;
}

void RawDataParser::Bind(MeasuringSystemContext* measuringSystem, EquipmentContext*& equipmentItem, DbContext* dbContext)
{
	BindingContext* binding = new BindingContext();
	binding->SetFKMeasuringSystem(measuringSystem->GetId());
	binding->SetFKEquipment(equipmentItem->GetId());
	measuringSystem->AddNewBinding(binding);
	equipmentItem->SetBinding(binding);
}

QStringList RawDataParser::GetCoordinates(QString line)
{
	bool xFlag = true;
	QString x = "";
	QString y = "";
	QStringList coordinate;
	
	for (int i = 0; i < line.length(); i++)
	{
		if (line.at(i) != ' ')
		{
			if (xFlag)
			{
				x += line.at(i);
			}
			else
			{
				y += line.at(i);
			}
		}
		else
		{
			if (!x.isEmpty())
			{
				xFlag = false;
			}
		}
	}

	coordinate.append(x);
	coordinate.append(y);
	return coordinate;
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

void RawDataParser::createMeasuringSystem(QMap<QString, QString> credentials)
{
	this->measuringSystem->SetName(credentials["name"]);
	QString description = credentials["description"];
	
	if (description != "")
	{
		this->measuringSystem->SetDescription(description);
	}

	this->measuringSystem->SetMainContributorName(credentials["contributor"]);
}