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
    void AddNewMeasurement(MeasurementContext* measurement);
    void AddNewSample(SampleContext* sample);
    void AddNewEquipment(EquipmentContext* equipment);
    void AddNewCharacteristicType(CharacteristicTypeContext* characteristicType);
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
