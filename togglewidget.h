#ifndef TOGGLEWIDGET_H
#define TOGGLEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

class ToggleWidget : public QWidget
{
    Q_OBJECT

public:
    ToggleWidget(QWidget *parent = nullptr);
    ~ToggleWidget();
signals:
    void modeSingle();
    void modeMultiple();
private slots:
    void changeMode();
private:
    QHBoxLayout* layout;
    QPushButton* changeBtn;
    QLabel* textLbl;
};
#endif // TOGGLEWIDGET_H
