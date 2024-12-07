#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    centralWidg = new QWidget(this);
    layout = new QVBoxLayout(centralWidg);
    centralWidg->setLayout(layout);

    // vars = new std::vector<double>(36, 0.0);
    std::array<double, 36>* vars = new std::array<double, 36>{};
    // toggleWidg = new ToggleWidget(centralWidg);
    // layout->addWidget(toggleWidg);
    // btnNext = new QPushButton("Следующий шаг", centralWidg);
    // layout->addWidget(btnNext);
    InputWidget* inp = new InputWidget(vars, this);
    layout->addWidget(inp);

    QPushButton* btnSubmit = new QPushButton("Подтвердить введенные данные", this);
    layout->addWidget(btnSubmit);

    this->setCentralWidget(centralWidg);

    calc = new CalculatorWidget(vars, this);
    calc->hide();
    connect(btnSubmit, &QPushButton::clicked, this, &MainWindow::startCalc);

    //ДЛЯ ОТЛАДКИ
    this->startCalc();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete vars;
}

void MainWindow::startCalc()
{
    calc->show();
    calc->calculate();
    this->setCentralWidget(calc);
}