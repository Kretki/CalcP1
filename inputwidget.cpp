#include "inputwidget.h"

Calculator::Calculator(){};

double Calculator::calculate(std::string input)
{
    bool check = false;
    double dFirst;
    double dSecond;
    double res = 0;
    for(int i = 0; i<input.size(); ++i)
    {
        if(!check)
        {
            if((input[i]>='0' && input[i]<='9') || (input[i] == '.')) 
            {
                sFirst+=input[i];
            } 
            else 
            {
                check = true;
                sign += input[i];
            }
        } 
        else 
        {
            sSecond+=input[i];
        }
    }
    dFirst = std::stod(sFirst);
    dSecond = std::stod(sSecond);
    if(sign == "+")
    {
        res = dFirst+dSecond;
    } 
    else if(sign == "-")
    {
        res = dFirst-dSecond;
    }
    else if(sign == "*")
    {
        res = dFirst*dSecond;
    }
    else if(sign == "/")
    {
        res = dFirst/dSecond;
    }
    return res;
};


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

    Calculator calc = Calculator();
    double res = calc.calculate(QString("10.1*20").toStdString());
    
    QString resultText = QString::number(res);

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

