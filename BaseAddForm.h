#pragma once

#pragma once

#include <QtWidgets/QWidget>

class BaseAddForm : public QWidget
{
    Q_OBJECT

public:
    BaseAddForm(QWidget* parent = Q_NULLPTR);

    void SetIsRowAdded(bool isRowAdded);

    bool GetIsRowAdded();

signals:
    void windowClosed();

protected:
    void closeEvent(QCloseEvent* event) override;
    
    bool isRowAdded = false;
};
