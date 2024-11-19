#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QDebug>

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class Calculator
{
public:
    Calculator();
    double calculate(std::string input);
private:
    std::string sFirst = "";
    std::string sign = "";
    std::string sSecond = "";
};

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QString>
#include <QRegularExpression>
#include <QtMath>
#include <QRegularExpression>

class InputWidgetBlock : public QWidget
{
    Q_OBJECT

public:
    InputWidgetBlock(QString title, QWidget *parent = nullptr);
// signals:
//     void lineSubmit(QLineEdit* input, QLabel* output);
private slots:
    void calculateExpr();
private:
    QVBoxLayout* layout;
    QHBoxLayout* inOutLayout;

    QLabel* titleLbl;
    QLineEdit* input;
    QLabel* output;
};

class InputWidget : public QWidget
{
    Q_OBJECT

public:
    InputWidget(QWidget *parent = nullptr);
private:
    QVBoxLayout* layout;
};
#endif // INPUTWIDGET_H
