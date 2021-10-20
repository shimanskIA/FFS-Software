#pragma once

#include "SampleContext.h"
#include "EquipmentContext.h"
#include "CharacteristicTypeContext.h"
#include "MeasuringSystemContext.h"

#include <QList>

class DbContext
{

public:
    DbContext();
    ~DbContext();

    void AddNewSample(SampleContext* sample);
    void AddNewEquipment(EquipmentContext* equipment);
    void AddNewCharacteristicType(CharacteristicTypeContext* characteristicType);
    void SetMeasuringSystem(MeasuringSystemContext* measuringSystemContext);

    QList<SampleContext*> GetSamples();
    QList<CharacteristicTypeContext*> GetCharacteristicTypes();
    QList<EquipmentContext*> GetEquipments();
    MeasuringSystemContext* GetMeasuringSystem();

private:
    QList<SampleContext*> samples;
    QList<EquipmentContext*> equipments;
    QList<CharacteristicTypeContext*> characteristicTypes;
    MeasuringSystemContext* measuringSystem;
};
