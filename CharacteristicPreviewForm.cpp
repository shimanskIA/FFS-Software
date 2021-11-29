#include "CharacteristicPreviewForm.h"

CharacteristicPreviewForm::CharacteristicPreviewForm(QString title, QVector<double> x, QVector<double> y, int windowId, QWidget* parent) 
    : QWidget(parent), 
    zoomMode(true), 
    rubberBand(new QRubberBand(QRubberBand::Rectangle, this))
{
	ui.setupUi(this);
    this->windowId = windowId;
    ui.plotTitle->setText(title);
    ui.plotTitle->setAlignment(Qt::AlignHCenter);
    ui.plotPreview->clearGraphs();
    ui.plotPreview->addGraph();
    ui.plotPreview->graph(0)->setData(x, y);
    ui.plotPreview->xAxis->setLabel("x");
    ui.plotPreview->yAxis->setLabel("y");
    ui.plotPreview->xAxis->setRange(x.first(), x.last());
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::green);
    ui.plotPreview->graph(0)->setPen(pen);

    double minY = y[0], maxY = y[0];
    for (int i = 1; i < y.length(); i++)
    {
        if (y[i] < minY) minY = y[i];
        if (y[i] > maxY) maxY = y[i];
    }

    ui.plotPreview->yAxis->setRange(minY, maxY);
    ui.plotPreview->replot();
    connect(ui.plotPreview, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePressEvent(QMouseEvent*)));
    connect(ui.plotPreview, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(mouseReleaseEvent(QMouseEvent*)));
    connect(ui.plotPreview, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMoveEvent(QMouseEvent*)));
    connect(ui.plotPreview, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(mouseDoubleClickEvent(QMouseEvent*)));
}

CharacteristicPreviewForm::~CharacteristicPreviewForm()
{
    delete rubberBand;
}

void CharacteristicPreviewForm::setZoomMode(bool mode)
{
    zoomMode = mode;
}

void CharacteristicPreviewForm::mousePressEvent(QMouseEvent* event)
{
    if (zoomMode)
    {
        if (event->button() == Qt::RightButton)
        {
            origin = event->pos();
            rubberBand->setGeometry(QRect(origin, QSize()));
            rubberBand->show();
        }
        else
        {
            if (!this->previousXAxeRanges.isEmpty())
            {
                ui.plotPreview->xAxis->setRange(previousXAxeRanges.pop());
                ui.plotPreview->yAxis->setRange(previousYAxeRanges.pop());
                ui.plotPreview->replot();
            }
        }
    }
    QWidget::mousePressEvent(event);
}

void CharacteristicPreviewForm::mouseMoveEvent(QMouseEvent* event)
{
    if (rubberBand->isVisible())
    {
        rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
    }
    QWidget::mouseMoveEvent(event);
}

void CharacteristicPreviewForm::mouseReleaseEvent(QMouseEvent* event)
{
    if (rubberBand->isVisible())
    {
        previousXAxeRanges.push(ui.plotPreview->xAxis->range());
        previousYAxeRanges.push(ui.plotPreview->yAxis->range());
        const QRect& zoomRect = rubberBand->geometry();
        int xp1, yp1, xp2, yp2;
        zoomRect.getCoords(&xp1, &yp1, &xp2, &yp2);
        auto x1 = ui.plotPreview->xAxis->pixelToCoord(xp1);
        auto x2 = ui.plotPreview->xAxis->pixelToCoord(xp2);
        auto y1 = ui.plotPreview->yAxis->pixelToCoord(yp1);
        auto y2 = ui.plotPreview->yAxis->pixelToCoord(yp2);
        ui.plotPreview->xAxis->setRange(x1, x2);
        ui.plotPreview->yAxis->setRange(y1, y2);
        rubberBand->hide();
        ui.plotPreview->replot();
    }
    QWidget::mouseReleaseEvent(event);
}

void CharacteristicPreviewForm::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (!this->previousXAxeRanges.isEmpty())
    {
        ui.plotPreview->xAxis->setRange(previousXAxeRanges.first());
        ui.plotPreview->yAxis->setRange(previousYAxeRanges.first());
        this->previousXAxeRanges.clear();
        this->previousYAxeRanges.clear();
        ui.plotPreview->replot();
    }
    QWidget::mouseDoubleClickEvent(event);
}

void CharacteristicPreviewForm::closeEvent(QCloseEvent* event)
{
    emit previewWindowClosed(windowId);
    event->accept();
}