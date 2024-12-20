#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "togglewidget.h"
#include "inputwidget.h"
#include "calculatorwidget.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void startCalc();
private:
    Ui::MainWindow *ui;

    CalculatorWidget* calc;

    QWidget* centralWidg;
    QVBoxLayout* layout;

    ToggleWidget* toggleWidg;
    QPushButton* btnNext;

    std::vector<double>* vars;
};
#endif // MAINWINDOW_H
