#include "inputwidget.h"

InputWidget::InputWidget(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    this->setLayout(layout);

    
}

