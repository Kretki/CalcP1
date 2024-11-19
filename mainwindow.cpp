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

    // toggleWidg = new ToggleWidget(centralWidg);
    // layout->addWidget(toggleWidg);
    // btnNext = new QPushButton("Следующий шаг", centralWidg);
    // layout->addWidget(btnNext);
    InputWidget* inp = new InputWidget(this);
    layout->addWidget(inp);

    this->setCentralWidget(centralWidg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

