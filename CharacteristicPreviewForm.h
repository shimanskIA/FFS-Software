#pragma once

#include <QtWidgets/QWidget>
#include <QPoint>
#include <QRubberBand>
#include <QMouseEvent>

#include "ui_CharacteristicPreviewForm.h"

class CharacteristicPreviewForm : public QWidget
{
    Q_OBJECT

public:
    CharacteristicPreviewForm(QVector<double> x, QVector<double> y, int windowId, QWidget* parent = Q_NULLPTR);
    virtual ~CharacteristicPreviewForm();

    void setZoomMode(bool mode);

signals:
    void previewWindowClosed(int id);

private slots:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    Ui::CharacteristicPreviewFormClass ui;
    bool zoomMode;
    QRubberBand* rubberBand;
    QPoint origin;
    QList<QCPRange> previousXAxeRanges;
    QList<QCPRange> previousYAxeRanges;
    int windowId;
    void closeEvent(QCloseEvent* event) override;
};
