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

    toggleWidg = new ToggleWidget(centralWidg);
    layout->addWidget(toggleWidg);

    this->setCentralWidget(centralWidg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

