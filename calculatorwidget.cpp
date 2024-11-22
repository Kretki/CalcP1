#include "calculatorwidget.h"

CalculatorWidget::CalculatorWidget(std::array<double, 36>* vars, QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    this->setLayout(layout);

    this->vars = vars;
}

CalculatorWidget::~CalculatorWidget()
{
    delete layout;
    delete vars;
}

void CalculatorWidget::calculate()
{
    qDebug() << vars->at(0);
}