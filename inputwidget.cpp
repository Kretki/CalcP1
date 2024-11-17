#include "inputwidget.h"

InputWidget::InputWidget(QWidget *parent)
    : QMainWindow(parent)
{
    layout = new QVBoxLayout(this);
    this->setLayout(layout);
}

