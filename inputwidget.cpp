#include "inputwidget.h"

Calculator::Calculator(){};

double Calculator::calculateString(std::string input)
{
    std::vector<std::pair<std::string, int>> priors;
    std::vector<double> numbers;
    std::string curNumber = "";
    std::string sign = "";
    int curPrior = 0;
    for(int i = 0; i<input.size(); ++i)
    {
        if(!((input[i]>='0' && input[i]<='9') || (input[i] == '.' || input[i] == ',')))
        {
            sign += input[i];
        }
        else if (sign != "")
        {
            numbers.push_back(std::stod(curNumber));
            curNumber = "";
            if(sign == "+" || sign == "-")
            {
                priors.push_back({sign, curPrior+0});
            }
            else if(sign == "*" || sign == "/")
            {
                priors.push_back({sign, curPrior+1});
            }
            else if(sign == "^") //|| sign == "**")
            {
                priors.push_back({"^", curPrior+2});
            }
            else if(sign == "(")
            {
                curPrior += 3;
            }
            else if(sign == ")")
            {
                curPrior -= 3;
            }
            sign = "";
            curNumber += input[i];
        }
        else if(sign == "")
        {
            curNumber += input[i];
        }
    }

    if(curNumber != "")
    {
        numbers.push_back(std::stod(curNumber));
        curNumber = "";
    }
    for(int i = 0; i<priors.size(); ++i)
    {
        qDebug() << QString().fromStdString(priors[i].first) << ' ' << priors[i].second;
    }
    for(int i = 0; i<numbers.size(); ++i)
    {
        qDebug() << numbers[i];
    }
    return 0.;
}

double Calculator::calculateExpr(std::string input)
{
    bool endFirst = false;
    bool endSign = false;
    double dFirst;
    double dSecond;
    double res = 0;
    for(int i = 0; i<input.size(); ++i)
    {
        if(!endFirst)
        {
            if((input[i]>='0' && input[i]<='9') || (input[i] == '.' || input[i] == ',')) 
            {
                if(input[i] == ',')
                    sFirst += '.';
                else
                    sFirst += input[i];
            } 
            else 
            {
                endFirst = true;
                sign += input[i];
            }
        } 
        else if(!endSign){
            if(!((input[i]>='0' && input[i]<='9') || (input[i] == '.' || input[i] == ',')))
            {
                sign += input[i];
            }
            else
            {
                endSign = true;
                sSecond += input[i];
            }
        }
        else
        {
            if(input[i] == ',')
                sSecond += '.';
            else
                sSecond += input[i];
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
    else if(sign == "^" || sign == "**")
    {
        res = std::pow(dFirst,dSecond);
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

    Calculator calc = Calculator();
    double res = calc.calculateString(QString("10.1+20+(10+10)").toStdString());
    
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

