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
            else if(sign == "^-")
            {
                priors.push_back({"^-", curPrior+2});
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
        else if(sign == "^-")
        {
            res = std::pow(first,-second);
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

ShowWidgetBlock::ShowWidgetBlock(QString title, QString unit, std::array<double, 36>* vars, QWidget *parent)
{
    layout = new QVBoxLayout(this);
    this->setLayout(layout);

    titleLbl = new QLabel(title, this);
    layout->addWidget(titleLbl);

    this->unit = unit;
    this->vars = vars;

    // input->setPlaceholderText(placeholder);
    output = new QLabel(this);
    layout->addWidget(output);

    this->setMaximumHeight(QFontMetrics(output->font()).height()*5);
}

ShowWidgetBlock::~ShowWidgetBlock()
{
    // delete vars;
}
void ShowWidgetBlock::valuesChanged()
{
    if(titleLbl->text() == "Период повторения")
    {
        if(vars->at(9) != 0.)
        {
            output->setText(QString::number(1/vars->at(9)) + " " + this->unit);
            vars->at(10) = 1/vars->at(9);
        }
    }
    else if(titleLbl->text() == "Девиация")
    {
        if(vars->at(6) != 0.)
        {
            output->setText(QString::number(vars->at(8)/(2*vars->at(6))) + " " + this->unit);
            vars->at(14) = vars->at(8)/(2*vars->at(6));
        }
    }
    else
    {
        if(vars->at(8) != 0.)
        {
            output->setText(QString::number(2*vars->at(6)/vars->at(8)) + " " + this->unit);
            vars->at(12) = 2*vars->at(6)/vars->at(8);
            vars->at(13) = 2*vars->at(6)/vars->at(8);
            vars->at(15) = 2*vars->at(6)/vars->at(8);
        }
    }
}

InputWidgetBlock::InputWidgetBlock(QString title, QString unit, double& var, QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    this->setLayout(layout);

    titleLbl = new QLabel(title, this);
    layout->addWidget(titleLbl);

    this->unit = unit;
    this->var = &var;

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

InputWidgetBlock::~InputWidgetBlock()
{
    // delete var;
}

void InputWidgetBlock::setText(QString text)
{
    this->input->setText(text);
};

void InputWidgetBlock::calculateExpr()
{
    QString expression = input->text();

    Calculator calc = Calculator();
    std::pair<double, bool> res = calc.calculateString(expression.toStdString());

    if(res.second)
    {
        QString resultText = QString::number(res.first);
        *(this->var) = res.first;
        output->setText(resultText + " " + this->unit);
    }
}

InputWidget::InputWidget(std::array<double, 36>* vars, QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    this->setLayout(layout);

    scrollWidg = new QWidget(this);
    scrollLayout = new QVBoxLayout(scrollWidg);
    scrollWidg->setLayout(scrollLayout);
    scrollWidg->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //RLS params (rls)
    QPushButton* btnRls = new QPushButton("Загрузить из файла inputRLS.txt", this);
    scrollLayout->addWidget(btnRls);

    InputWidgetBlock* rls1 = new InputWidgetBlock("Импульсная мощность РЛС", "Вт", vars->at(0), this);
    InputWidgetBlock* rls2 = new InputWidgetBlock("КУ антенны", "", vars->at(1), this);
    InputWidgetBlock* rls3 = new InputWidgetBlock("КШ приемника", "", vars->at(2), this);
    InputWidgetBlock* rls4 = new InputWidgetBlock("Рабочая частота", "Гц", vars->at(3), this);
    InputWidgetBlock* rls5 = new InputWidgetBlock("ВЛТ", "", vars->at(4), this);
    InputWidgetBlock* rls6 = new InputWidgetBlock("Пороговая вероятность обнаружения", "", vars->at(5), this);
    InputWidgetBlock* rls7 = new InputWidgetBlock("Разрешающая способность по дальности", "", vars->at(6), this);
    InputWidgetBlock* rls8 = new InputWidgetBlock("Разрешающая способность по скорости", "", vars->at(7), this);

    rlsVec = {rls1, rls2, rls3, rls4, rls5, rls6, rls7, rls8};

    for(int i = 0; i<rlsVec.size(); ++i)
    {
        scrollLayout->addWidget(rlsVec[i]);
    }
    // this->readFromFile(rlsVec, "inputRLS.txt");
    connect(btnRls, &QPushButton::clicked, this, [this](){ this->readFromFile(rlsVec, "inputRLS.txt"); });
    //Signal params (s)
    QPushButton* btnS = new QPushButton("Загрузить из файла inputSig.txt", this);
    scrollLayout->addWidget(btnS);

    InputWidgetBlock* s1 = new InputWidgetBlock("Скорость света", "м/c", vars->at(8), this);
    InputWidgetBlock* s2 = new InputWidgetBlock("Частота повторения", "Гц", vars->at(9), this);
    ShowWidgetBlock* s3 = new ShowWidgetBlock("Период повторения", "с", vars, this);
    connect(s2->input, &QLineEdit::textChanged, s3, &ShowWidgetBlock::valuesChanged);
    InputWidgetBlock* s4 = new InputWidgetBlock("Время контакта с целью", "с", vars->at(11), this);
    ShowWidgetBlock* s5 = new ShowWidgetBlock("Длительность импульсного сигнала", "", vars, this);
    connect(rls7->input, &QLineEdit::textChanged, s5, &ShowWidgetBlock::valuesChanged);
    connect(s1->input, &QLineEdit::textChanged, s5, &ShowWidgetBlock::valuesChanged);
    ShowWidgetBlock* s6 = new ShowWidgetBlock("Длительность ЛЧМ сигнала", "", vars, this);
    connect(rls7->input, &QLineEdit::textChanged, s6, &ShowWidgetBlock::valuesChanged);
    connect(s1->input, &QLineEdit::textChanged, s6, &ShowWidgetBlock::valuesChanged);
    ShowWidgetBlock* s7 = new ShowWidgetBlock("Девиация", "", vars, this);
    connect(rls7->input, &QLineEdit::textChanged, s7, &ShowWidgetBlock::valuesChanged);
    connect(s1->input, &QLineEdit::textChanged, s7, &ShowWidgetBlock::valuesChanged);
    ShowWidgetBlock* s8 = new ShowWidgetBlock("Длитльность кванта ФМ сигнала", "", vars, this);
    connect(rls7->input, &QLineEdit::textChanged, s8, &ShowWidgetBlock::valuesChanged);
    connect(s1->input, &QLineEdit::textChanged, s8, &ShowWidgetBlock::valuesChanged);
    InputWidgetBlock* s9 = new InputWidgetBlock("Скважность ФМ сигнала", "", vars->at(16), this);

    sVec = {s1, s2, s4, s9};

    scrollLayout->addWidget(s1);
    scrollLayout->addWidget(s2);
    scrollLayout->addWidget(s3);
    scrollLayout->addWidget(s4);
    scrollLayout->addWidget(s5);
    scrollLayout->addWidget(s6);
    scrollLayout->addWidget(s7);
    scrollLayout->addWidget(s8);
    scrollLayout->addWidget(s9);

    connect(btnS, &QPushButton::clicked, this, [this](){ this->readFromFile(sVec, "inputSig.txt"); });
    //Target params (t)
    QPushButton* btnT = new QPushButton("Загрузить из файла inputTarg.txt", this);
    scrollLayout->addWidget(btnT);

    InputWidgetBlock* t1 = new InputWidgetBlock("ЭПР цели", "м^2", vars->at(17), this);
    InputWidgetBlock* t2 = new InputWidgetBlock("Дальность цели", "m", vars->at(18), this);
    InputWidgetBlock* t3 = new InputWidgetBlock("Затухание на трассе", "дБ/км", vars->at(19), this);

    tVec = {t1, t2, t3};

    for(int i = 0; i<tVec.size(); ++i)
    {
        scrollLayout->addWidget(tVec[i]);
    }

    connect(btnT, &QPushButton::clicked, this, [this](){ this->readFromFile(tVec, "inputTarg.txt"); });
    //Noise params (n)
    QPushButton* btnN = new QPushButton("Загрузить из файла inputNoise.txt", this);
    scrollLayout->addWidget(btnN);

    InputWidgetBlock* n1 = new InputWidgetBlock("Спектральная плотность мощности помехи", "Вт/Гц", vars->at(20), this);
    InputWidgetBlock* n2 = new InputWidgetBlock("Эффективная ширина спектра помехи", "Гц", vars->at(21), this);
    InputWidgetBlock* n3 = new InputWidgetBlock("Максимальный КУ антенны САП", "", vars->at(22), this);
    InputWidgetBlock* n4 = new InputWidgetBlock("Уровень нормированной ДН РЛС в направлении САП", "", vars->at(23), this);
    InputWidgetBlock* n5 = new InputWidgetBlock("Расхождение поляризаций антенн РЛС и САП", "", vars->at(24), this);
    InputWidgetBlock* n6 = new InputWidgetBlock("Дальность САП в режиме помеха прикрытия", "", vars->at(25), this);

    nVec = {n1, n2, n3, n4, n5, n6};

    for(int i = 0; i<nVec.size(); ++i)
    {
        scrollLayout->addWidget(nVec[i]);
    }

    connect(btnN, &QPushButton::clicked, this, [this](){ this->readFromFile(nVec, "inputNoise.txt"); });
    //Receiver (rec)
    QPushButton* btnRec = new QPushButton("Загрузить из файла inputReceiver.txt", this);
    scrollLayout->addWidget(btnRec);

    InputWidgetBlock* rec1 = new InputWidgetBlock("Дальность разведприемника", "м", vars->at(26), this);
    InputWidgetBlock* rec2 = new InputWidgetBlock("КУ антенны", "", vars->at(27), this);
    InputWidgetBlock* rec3 = new InputWidgetBlock("Уровень нормированной ДН РЛС в направлении РП", "", vars->at(28), this);
    InputWidgetBlock* rec4 = new InputWidgetBlock("Коэффициент шума приемника", "", vars->at(29), this);
    InputWidgetBlock* rec5 = new InputWidgetBlock("ВПО", "", vars->at(30), this);
    InputWidgetBlock* rec6 = new InputWidgetBlock("ВЛТ", "", vars->at(31), this);
    InputWidgetBlock* rec7 = new InputWidgetBlock("Ширина ПП приемника", "", vars->at(32), this);
    InputWidgetBlock* rec8 = new InputWidgetBlock("Время интегрирования", "", vars->at(33), this);
    InputWidgetBlock* rec9 = new InputWidgetBlock("Коэффициент энергетических потерь", "", vars->at(34), this);
    InputWidgetBlock* rec10 = new InputWidgetBlock("Расхождение поляризаций антенн РЛС и РП", "", vars->at(35), this);

    recVec = {rec1, rec2, rec3, rec4, rec5, rec6, rec7, rec8, rec9, rec10};

    for(int i = 0; i<recVec.size(); ++i)
    {
        scrollLayout->addWidget(recVec[i]);
    }

    connect(btnRec, &QPushButton::clicked, this, [this](){ this->readFromFile(recVec, "inputReceiver.txt"); });

    scrollArea = new QScrollArea();
    scrollArea->setWidget(scrollWidg);
    scrollArea->setWidgetResizable(true);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(scrollArea, 1);

    //ДЛЯ ОТЛАДКИ
    this->readFromFile(rlsVec, "inputRLS.txt");
    this->readFromFile(sVec, "inputSig.txt");
    this->readFromFile(tVec, "inputTarg.txt");
    this->readFromFile(nVec, "inputNoise.txt");
    this->readFromFile(recVec, "inputReceiver.txt");
}

InputWidget::~InputWidget()
{
    for(auto p : rlsVec)
    {
        delete p;
    }
    rlsVec.clear();
    for(auto p : sVec)
    {
        delete p;
    }
    sVec.clear();
    for(auto p : tVec)
    {
        delete p;
    }
    tVec.clear();
    for(auto p : nVec)
    {
        delete p;
    }
    nVec.clear();
    for(auto p : recVec)
    {
        delete p;
    }
    recVec.clear();
}

void InputWidget::readFromFile(std::vector<InputWidgetBlock*> lines, QString filename)
{
    QFile file(QCoreApplication::applicationDirPath()+"/"+filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) 
        return;
    QTextStream in(&file);
    QStringList fields = in.readLine().split(";");
    for(int i = 0; i<lines.size(); ++i)
    {
        lines[i]->setText(fields[i]);
    }
};