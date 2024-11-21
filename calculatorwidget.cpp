#include "calculatorwidget.h"

CalculatorWidget::CalculatorWidget(Variables& vars, QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    this->setLayout(layout);
}

CalculatorWidget::~CalculatorWidget()
{
    delete layout;
}

void CalculatorWidget::calculate()
{
    qDebug() << vars.Dc;
}