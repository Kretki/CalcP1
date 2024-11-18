#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

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

#include <QDebug>

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
