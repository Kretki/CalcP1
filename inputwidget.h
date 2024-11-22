#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <iostream>
#include <cmath>
#include <string>
#include <utility>
#include <vector>

class Calculator
{
public:
    Calculator();
    std::pair<double, bool> calculateString(std::string input);
};

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QString>
#include <QScrollArea>
#include <QCoreApplication>
#include <QTextStream>

class ShowWidgetBlock : public QWidget
{
    Q_OBJECT

public:
    ShowWidgetBlock(QString title, QString unit, std::array<double, 36>* vars, QWidget *parent = nullptr);
    ~ShowWidgetBlock();
public slots:
    void valuesChanged();
private:
    QVBoxLayout* layout;

    QString unit;

    QLabel* titleLbl;
    QLabel* output;

    std::array<double, 36>* vars;
};

class InputWidgetBlock : public QWidget
{
    Q_OBJECT

public:
    InputWidgetBlock(QString title, QString unit, double& var, QWidget *parent = nullptr);
    ~InputWidgetBlock();
    void setText(QString text);
    
    QLineEdit* input;
private slots:
    void calculateExpr();
private:
    QVBoxLayout* layout;
    QHBoxLayout* inOutLayout;

    QString unit;

    QLabel* titleLbl;
    QLabel* output;

    double* var;
};

class InputWidget : public QWidget
{
    Q_OBJECT

public:
    InputWidget(std::array<double, 36>* vars, QWidget *parent = nullptr);
    ~InputWidget();
private slots:
    void readFromFile(std::vector<InputWidgetBlock*> lines, QString filename);
private:
    QVBoxLayout* layout;
    QVBoxLayout* scrollLayout;
    QScrollArea* scrollArea;
    QWidget* scrollWidg;

    std::vector<InputWidgetBlock*> rlsVec;
    std::vector<InputWidgetBlock*> sVec;
    std::vector<InputWidgetBlock*> tVec;
    std::vector<InputWidgetBlock*> nVec;
    std::vector<InputWidgetBlock*> recVec;
};
#endif // INPUTWIDGET_H
