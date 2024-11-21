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

    Variables vars;

    // toggleWidg = new ToggleWidget(centralWidg);
    // layout->addWidget(toggleWidg);
    // btnNext = new QPushButton("Следующий шаг", centralWidg);
    // layout->addWidget(btnNext);
    InputWidget* inp = new InputWidget(vars, this);
    layout->addWidget(inp);

    QPushButton* btnSubmit = new QPushButton("Подтвердить введенные данные", this);
    layout->addWidget(btnSubmit);

    this->setCentralWidget(centralWidg);

    CalculatorWidget* calc = new CalculatorWidget(vars, this);

    connect(btnSubmit, &QPushButton::clicked, calc, &CalculatorWidget::calculate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

