#pragma once

#include "FFSDatabaseInterface.h"
#include "MeasuringSystemInputForm.h"

#include <QString>
#include <QObject>

class WindowManager : public QObject
{
public:
	WindowManager();

	void ManageWindows(QString tableName, FFSDatabaseInterface* view, QMap<QString, int> foreignKeys = QMap<QString, int>());
	void ShowCharacteristicPreview(QVector<double> x, QVector<double> y, FFSDatabaseInterface* view, int fk_characteristic);
	void BindMeasuringSystemToInputForm();

private slots:
	void redirectInitializeMeasuringSystemRequest(QMap<QString, QString> credentials);
};
