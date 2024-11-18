#include "inputwidget.h"

InputWidgetBlock::InputWidgetBlock(QString title, QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    this->setLayout(layout);

    titleLbl = new QLabel(title, this);
    layout->addWidget(titleLbl);

    inOutLayout = new QHBoxLayout();
    input = new QLineEdit(this);
    // input->setPlaceholderText(placeholder);
    output = new QLabel(this);
    inOutLayout->addWidget(input, 1);
    inOutLayout->addWidget(output, 1);
    layout->addLayout(inOutLayout);
    connect(input, &QLineEdit::textChanged, this, &InputWidgetBlock::calculateExpr);
}

void InputWidgetBlock::calculateExpr()
{
    QString expression = input->text();
    QString fractionResult;


    QString modExpression = expression;
    modExpression.replace(QRegularExpression("\\^"), "**");
    double decimalResult = 0.0;
    // toFraction(decimalResult);
    QString resultText = QString::number(decimalResult);

    output->setText(resultText);
}

InputWidget::InputWidget(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    this->setLayout(layout);

    //RLS params (rls)
    InputWidgetBlock* rls1 = new InputWidgetBlock("Импульсная мощность РЛС", this);
    layout->addWidget(rls1);
    //Signal params (s)
    //Target params (t)
    //Noise params (n)
    //Receiver (rec)
}

