#pragma once

#include "MeasurementContext.h"
#include "MeasurementParameterContext.h"
#include "SampleContext.h"
#include "MeasuringSystemContext.h"
#include "EquipmentContext.h"
#include "EquipmentParameterContext.h"
#include "CharacteristicsContext.h"
#include "CharacteristicTypeContext.h"
#include "EquipmentHasMeasuringSystemContext.h"

#include <QList>

class DbContext
{

public:
    DbContext();
    ~DbContext();
    void AddNewMeasurement(MeasurementContext measurementContext);
    void AddNewMeasurementParameter(MeasurementParameterContext measurementParameterContext);
    void AddNewSample(SampleContext sampleContext);
    void AddNewMeasuringSystem(MeasuringSystemContext measuringSystemContext);
    void AddNewEquipment(EquipmentContext equipmentContext);
    void AddNewEquipmentParameter(EquipmentParameterContext equipmentParameterContext);
    void AddNewCharacteristicsSet(CharacteristicsContext characteristicsContext);
    void AddNewCharacteristicType(CharacteristicTypeContext characteristicTypeContext);
    void AddNewBinding(EquipmentHasMeasuringSystemContext binding);

private:
    QList<MeasurementContext> measurements;
    QList<MeasurementParameterContext> measurementParameters;
    QList<SampleContext> samples;
    QList<MeasuringSystemContext> measuringSystems;
    QList<EquipmentContext> equipments;
    QList<EquipmentParameterContext> equipmentParameters;
    QList<CharacteristicsContext> characteristics;
    QList<CharacteristicTypeContext> characteristicTypes;
    QList<EquipmentHasMeasuringSystemContext> bindings;
};
