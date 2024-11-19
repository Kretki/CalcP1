#include "inputwidget.h"

Calculator::Calculator(){};

std::pair<double, bool> Calculator::calculateString(std::string input)
{
    if(std::string("+-*/^").find(input[input.size()-1]) != std::string::npos)
    {
        input.pop_back();
    }
    if(std::count(input.begin(), input.end(), '(') != std::count(input.begin(), input.end(), ')'))
    {
        return {-1, false};
    }
    std::vector<std::pair<std::string, int>> priors;
    std::vector<double> numbers;
    std::string curNumber = "";
    std::string sign = "";
    int curPrior = 0;
    size_t startBracket = input.find_first_of("(")+1;
    size_t endBracket = input.find_last_of(")");
    if(endBracket != std::string::npos)
    {
        std::string bracketSub = input.substr(startBracket, endBracket-startBracket);
        double sub = calculateString(bracketSub).first;
        input.replace(startBracket-1, endBracket-startBracket+2, std::to_string(sub));
    }
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
    
    while(priors.size() != 0)
    {
        int curPrior = 0;
        int pos = 0;
        for(int i = 0; i<priors.size(); ++i)
        {
            curPrior = std::max(priors[i].second, curPrior);
            pos = i;
        }
        
        std::string sign = priors[pos].first;
        double first = numbers[pos];
        double second = numbers[pos+1];
        double res;

        if(sign == "+") 
        {
            res = first+second;
        }
        else if(sign == "-")
        {
            res = first-second;
        }
        else if(sign == "*")
        {
            res = first*second;
        }
        else if(sign == "/")
        {
            res = first/second;
        }
        else if(sign == "^")
        {
            res = std::pow(first,second);
        }
        
        priors.erase(priors.begin()+pos);
        numbers.erase(numbers.begin()+pos+1);
        numbers.erase(numbers.begin()+pos);
        numbers.insert(numbers.begin()+pos, res);
    }
    return {numbers[0], true};
}


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

    Calculator calc = Calculator();
    std::pair<double, bool> res = calc.calculateString(expression.toStdString());

    if(res.second)
    {
        QString resultText = QString::number(res.first);
        output->setText(resultText);
    }
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

