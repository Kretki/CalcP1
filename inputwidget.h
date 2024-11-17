#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class InputWidget : public QWidget
{
    Q_OBJECT

public:
    InputWidget(QWidget *parent = nullptr);

private:
    QVBoxLayout* layout;
};
#endif // INPUTWIDGET_H
