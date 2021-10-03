#pragma once

#include <QString>
#include <QMap>

class DbContext
{

public:
    DbContext();
    void SetMeasurementName(QString measurementName);
    void SetMeasurementDate(QString measurementDate);
    void SetMeasurementFileLink(QString measurementFileLink);
    void SetNumberOfPoints(QString measurementFileLink);
    void SetBinTime(QString binTime);
    void SetSampleName(QString sampleName);
    void SetSampleDescription(QString sampleDescription);
    void SetMeasurementParameters(QString parameterName, QString parameterValue);
    void SetMeasuringSystemName(QString measuringSystemName);
    void SetEquipment(QString equipmentName, QString equipmentDescription);
    void SetEquipmentParameters(QString parameterName, QString parameterValue);

private:
    QString measurementName;
    QString measurementDate;
    QString measurementFileLink;
    int numberOfPoints;
    double binTime;

    QString sampleName;
    QString sampleDescription;

    QMap<QString, double> measurementParameters;

    QString measuringSystemName;

    QMap<QString, QString> equipment;

    QMap<QString, double> equipmentParameters;

};
