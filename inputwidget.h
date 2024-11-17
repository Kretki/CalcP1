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
#include <QStringList>

class InputWidget : public QWidget
{
    Q_OBJECT

public:
    InputWidget(QWidget *parent = nullptr);

private:
    QVBoxLayout* layout;
};
#endif // INPUTWIDGET_H
