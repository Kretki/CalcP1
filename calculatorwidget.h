#ifndef CALCULATORWIDGET_H
#define CALCULATORWIDGET_H

struct Variables
{
    // Параметры РЛС
    double Pi;      //Импульсная мощность РЛС
    double Gc;      //КУ антенны
    double Nsh;     //КШ приемника
    double fc;      //Рабочая частота
    double Fc;      //ВЛТ
    double Dpor;    //Пороговая вероятность обнаружения
    double delR;    //Разрешающая способность по дальности
    double delVr;   //Разрешающая способность по скорости
    // Сигнал и обработка
    double c;       //Скорость света
    double Fpsig;   //Частота повторения
    double Tpsig;   //Период повторения
    double Tk;      //Время контакта с целью
    double tcimp;   //Длительность импульсного сигнала
    double tclcm;   //Длительность ЛЧМ сигнала
    double W;       //Девиация
    double tkv;     //Длительность ФМ кванта
    double Q;       //Скважность
    //Цель и трасса
    double eprc;    //ЭПР цели
    double Dc;      //Дальность цели
    double alpha;   //Затухание на трассе
    //Помеха
    double Spp;     //Спектральная плотность мощности помехи
    double delFp;   //Эффективная ширина спектра помехи
    double GpNoise; //Макимальный КУ антенны САП
    double Apom;    //Уровень нормированной ДН РЛС в направлении САП
    double gammaPNoise;//Расхождение поляризаций антенн РЛС и САП
    double Dp;      //Дальность САП в режиме помеха прикрытия
    //Разведприемник
    double Rp;      //Дальность разведприемника
    double GpRec;   //КУ антенны
    double Arp;     //Уровень нормированной ДН РЛС в направлении РП
    double Nshr;    //КШ приемника
    double Do;      //ВПО
    double FpRec;   //ВЛТ
    double delFpRec;//Ширина ПП приемника
    double TpRec;   //Время интегрирования
    double ro;      //Коэффициент энергетических потерь
    double gammaPRec;//Расхождение поляризаций антенн РЛС и РП
};

#include <QDebug>

#include <QWidget>
#include <QVBoxLayout>

class CalculatorWidget : public QWidget
{
    Q_OBJECT

public:
    CalculatorWidget(Variables& vars, QWidget *parent = nullptr);
    ~CalculatorWidget();
public slots:
    void calculate();
private:
    QVBoxLayout* layout;

    Variables vars;
};

#endif // CALCULATORWIDGET_H