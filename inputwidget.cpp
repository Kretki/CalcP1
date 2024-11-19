#include "inputwidget.h"

Calculator::Calculator(){};

std::pair<double, bool> Calculator::calculateString(std::string input)
{
    if(input == "")
    {
        return {0, true};
    }
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


InputWidgetBlock::InputWidgetBlock(QString title, QString unit, QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    this->setLayout(layout);

    titleLbl = new QLabel(title, this);
    layout->addWidget(titleLbl);

    this->unit = unit;

    inOutLayout = new QHBoxLayout();
    input = new QLineEdit(this);
    // input->setPlaceholderText(placeholder);
    output = new QLabel(this);
    inOutLayout->addWidget(input, 1);
    inOutLayout->addWidget(output, 1);
    layout->addLayout(inOutLayout);
    connect(input, &QLineEdit::textChanged, this, &InputWidgetBlock::calculateExpr);

    this->setMaximumHeight(QFontMetrics(input->font()).height()*5);
}

void InputWidgetBlock::calculateExpr()
{
    QString expression = input->text();

    Calculator calc = Calculator();
    std::pair<double, bool> res = calc.calculateString(expression.toStdString());

    if(res.second)
    {
        QString resultText = QString::number(res.first);
        output->setText(resultText + " " + this->unit);
    }
}

InputWidget::InputWidget(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    this->setLayout(layout);

    scrollWidg = new QWidget(this);
    scrollLayout = new QVBoxLayout(scrollWidg);
    scrollWidg->setLayout(scrollLayout);
    scrollWidg->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //RLS params (rls)
    QPushButton* btnRls = new QPushButton("Загрузить из файла inputRLS.txt", this)

    InputWidgetBlock* rls1 = new InputWidgetBlock("Импульсная мощность РЛС", "Вт", this);
    InputWidgetBlock* rls2 = new InputWidgetBlock("КУ антенны", "", this);
    InputWidgetBlock* rls3 = new InputWidgetBlock("КШ приемника", "", this);
    InputWidgetBlock* rls4 = new InputWidgetBlock("Рабочая частота", "Гц", this);
    InputWidgetBlock* rls5 = new InputWidgetBlock("ВЛТ", "", this);
    InputWidgetBlock* rls6 = new InputWidgetBlock("Пороговая вероятность обнаружения", "", this);
    InputWidgetBlock* rls7 = new InputWidgetBlock("Разрешающая способность по дальности", "", this);
    InputWidgetBlock* rls8 = new InputWidgetBlock("Разрешающая способность по скорости", "", this);
    
    scrollLayout->addWidget(rls1);
    scrollLayout->addWidget(rls2);
    scrollLayout->addWidget(rls3);
    scrollLayout->addWidget(rls4);
    scrollLayout->addWidget(rls5);
    scrollLayout->addWidget(rls6);
    scrollLayout->addWidget(rls7);
    scrollLayout->addWidget(rls8);
    //Signal params (s)
    //Target params (t)
    //Noise params (n)
    //Receiver (rec)

    scrollArea = new QScrollArea();
    scrollArea->setWidget(scrollWidg);
    scrollArea->setWidgetResizable(true);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(scrollArea, 1);
}

void InputWidget::readFromFile(std::vector<InputWidgetBlock*> lines, QString file)
{

};