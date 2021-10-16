#pragma once

#include "MeasurementContext.h"
#include "SampleContext.h"
#include "EquipmentContext.h"
#include "EquipmentParameterContext.h"
#include "CharacteristicTypeContext.h"
#include "BindingContext.h"

#include <QList>

class DbContext
{

public:
    DbContext();
    ~DbContext();
    void AddNewMeasurement(MeasurementContext* measurementContext);
    void AddNewSample(SampleContext* sampleContext);
    void AddNewEquipment(EquipmentContext* equipmentContext);
    void AddNewCharacteristicType(CharacteristicTypeContext* characteristicTypeContext);
    void AddNewBinding(BindingContext* binding);

    QList<SampleContext*> GetSamples();
    QList<CharacteristicTypeContext*> GetCharacteristicTypes();
    QList<MeasurementContext*> GetMeasurements();
    QList<EquipmentContext*> GetEquipments();
    QList<BindingContext*> GetBindings();

private:
    QList<MeasurementContext*> measurements;
    QList<SampleContext*> samples;
    QList<EquipmentContext*> equipments;
    QList<CharacteristicTypeContext*> characteristicTypes;
    QList<BindingContext*> bindings;
};
