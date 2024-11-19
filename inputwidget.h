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

class InputWidgetBlock : public QWidget
{
    Q_OBJECT

public:
    InputWidgetBlock(QString title, QString unit, QWidget *parent = nullptr);
// signals:
//     void lineSubmit(QLineEdit* input, QLabel* output);
private slots:
    void calculateExpr();
private:
    QVBoxLayout* layout;
    QHBoxLayout* inOutLayout;

    QString unit;

    QLabel* titleLbl;
    QLineEdit* input;
    QLabel* output;
};

class InputWidget : public QWidget
{
    Q_OBJECT

public:
    InputWidget(QWidget *parent = nullptr);
private slots:
    void readFromFile(std::vector<InputWidgetBlock*> lines, QString file);
private:
    QVBoxLayout* layout;
    QVBoxLayout* scrollLayout;
    QScrollArea* scrollArea;
    QWidget* scrollWidg;
};
#endif // INPUTWIDGET_H
