#include "togglewidget.h"

ToggleWidget::ToggleWidget(QWidget *parent)
    : QWidget(parent)
{
    layout = new QHBoxLayout(this);
    this->setLayout(layout);

    textLbl = new QLabel("Однопозиционная", this);
    layout->addWidget(textLbl);

    changeBtn = new QPushButton("Изменить тип", this);
    layout->addWidget(changeBtn);
    connect(changeBtn, &QPushButton::clicked, this, &ToggleWidget::changeMode);
}

ToggleWidget::~ToggleWidget()
{}

void ToggleWidget::changeMode() 
{
    if(textLbl->text() == "Однопозиционная")
    {
        textLbl->setText("Многопозиционная");
        emit modeMultiple();
    } else {
        textLbl->setText("Однопозиционная");
        emit modeSingle();
    }
}