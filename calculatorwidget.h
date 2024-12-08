#ifndef CALCULATORWIDGET_H
#define CALCULATORWIDGET_H

// class Variables
// {
// public:
//     Variables();
    // Параметры РЛС
    // double Pi;      //Импульсная мощность РЛС                        0
    // double Gc;      //КУ антенны                                     1
    // double Nsh;     //КШ приемника                                   2
    // double fc;      //Рабочая частота                                3
    // double Fc;      //ВЛТ                                            4
    // double Dpor;    //Пороговая вероятность обнаружения              5
    // double delR;    //Разрешающая способность по дальности           6
    // double delVr;   //Разрешающая способность по скорости            7
    // Сигнал и обработка
    // double c;       //Скорость света                                 8
    // double Fpsig;   //Частота повторения                             9
    // double Tpsig;   //Период повторения                              10
    // double Tk;      //Время контакта с целью                         11
    // double tcimp;   //Длительность импульсного сигнала               12
    // double tclcm;   //Длительность ЛЧМ сигнала                       13
    // double W;       //Девиация                                       14
    // double tkv;     //Длительность ФМ кванта                         15
    // double Q;       //Скважность                                     16
    //Цель и трасса
    // double eprc;    //ЭПР цели                                       17
    // double Dc;      //Дальность цели                                 18
    // double alpha;   //Затухание на трассе                            19
    //Помеха
    // double Spp;     //Спектральная плотность мощности помехи         20
    // double delFp;   //Эффективная ширина спектра помехи              21
    // double GpNoise; //Макимальный КУ антенны САП                     22
    // double Apom;    //Уровень нормированной ДН РЛС в направлении САП 23
    // double gammaPNoise;//Расхождение поляризаций антенн РЛС и САП    24
    // double Dp;      //Дальность САП в режиме помеха прикрытия        25
    //Разведприемник
    // double Rp;      //Дальность разведприемника                      26
    // double GpRec;   //КУ антенны                                     27
    // double Arp;     //Уровень нормированной ДН РЛС в направлении РП  28
    // double Nshr;    //КШ приемника                                   29
    // double Do;      //ВПО                                            30
    // double FpRec;   //ВЛТ                                            31
    // double delFpRec;//Ширина ПП приемника                            32
    // double TpRec;   //Время интегрирования                           33
    // double ro;      //Коэффициент энергетических потерь              34
    // double gammaPRec;//Расхождение поляризаций антенн РЛС и РП       35
// };

#include <vector>

#include <QDebug>

#include <QWidget>
#include <QVBoxLayout>
#include <QPen>
#include <QScrollArea>
#include <QWheelEvent>

#include <math.h>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_plot_zoomer.h>

class QwtPlotZoom : public QwtPlot
{
    Q_OBJECT
public:
    QwtPlotZoom(QWidget *parent = nullptr,  double* l_in_min=nullptr, double* l_in_max=nullptr, double* l_in_step=nullptr, double* b_in_min=nullptr, double* b_in_max=nullptr, double* b_in_step=nullptr);
    ~QwtPlotZoom();
protected:
    void wheelEvent(QWheelEvent *event) override;
private:
    QwtPlotZoomer* zoomer;
    double* l_min;
    double* l_max;
    double* l_step;
    double* b_min;
    double* b_max;
    double* b_step;
};


class CalculatorWidget : public QWidget
{
    Q_OBJECT

public:
    CalculatorWidget(std::array<double, 36>* vars, QWidget *parent = nullptr);
    ~CalculatorWidget();
public slots:
    void calculate();
private:
    void receive_base_data();
    void prob_true_discover_graphics();
    void noise_eff_coefficient_graphics();
    void self_defense_prob_true_discover_graphics();
    void self_defense_noise_eff_coefficient_graphics();


    double P_c(double Dc);
    double P_pp_imp(double Spp);
    double P_p_imp(double Dp, double Spp);
    double q_imp(double Dc, double Dp, double Spp);
    double D_imp(double Dc, double Dp, double Spp);
    
    double P_pp_lchm(double Spp);
    double P_p_lchm(double Dp, double Spp);
    double q_lchm(double Dc, double Dp, double Spp);
    double D_lchm(double Dc, double Dp, double Spp);

    double P_pp_fkm(double Spp);
    double P_p_fkm(double Dp, double Spp);
    double q_fkm(double Dc, double Dp, double Spp);
    double D_fkm(double Dc, double Dp, double Spp);

    double k_imp_eff_act_noise(double Dc, double Dp, double Spp);
    double k_lchm_eff_act_noise(double Dc, double Dp, double Spp);
    double k_fkm_eff_act_noise(double Dc, double Dp, double Spp);
    

    double P_c_self_defense(double Dp);

    double P_p_imp_self_defense(double Dp, double Spp);
    double P_p_lchm_self_defense(double Dp, double Spp);
    double P_p_fkm_self_defense(double Dp, double Spp);

    double q_imp_self_defense(double Dp, double Spp);
    double q_lchm_self_defense(double Dp, double Spp);
    double q_fkm_self_defense(double Dp, double Spp);

    double D_imp_self_defense(double Dp, double Spp);
    double D_lchm_self_defense(double Dp, double Spp);
    double D_fkm_self_defense(double Dp, double Spp);

    QVBoxLayout* layout;
    QVBoxLayout* scrollLayout;
    QScrollArea* scrollArea;
    QWidget* scrollWidg;

    std::array<double, 36>* vars;

    QwtPlot* graph_1_plot;
    QwtPlot* graph_2_plot;
    QwtPlot* graph_3_plot;
    QwtPlot* graph_4_plot;
    QwtPlot* graph_5_plot;
    QwtPlot* graph_6_plot;
    QwtPlot* graph_7_plot;
    QwtPlot* graph_8_plot;
    QwtPlot* graph_9_plot;

    // Параметры РЛС
    double Pi;      //Импульсная мощность РЛС                        0
    double Gc;      //КУ антенны                                     1
    double Nsh;     //КШ приемника                                   2
    double fc;      //Рабочая частота                                3
    double Fc;      //ВЛТ                                            4
    double Dpor;    //Пороговая вероятность обнаружения              5
    double delR;    //Разрешающая способность по дальности           6
    double delVr;   //Разрешающая способность по скорости            7
    // Сигнал и обработка
    double c;       //Скорость света                                 8
    double Fpsig;   //Частота повторения                             9
    double Tpsig;   //Период повторения                              10
    double Tk;      //Время контакта с целью                         11
    double tc_imp;   //Длительность импульсного сигнала               12
    double tc_lchm;   //Длительность ЛЧМ сигнала                       13
    double W;       //Девиация                                       14
    double tkv;     //Длительность ФМ кванта                         15
    double Q;       //Скважность                                     16
    //Цель и трасса
    double eprc;    //ЭПР цели                                       17
    double DcBase;      //Дальность цели                                 18
    double alpha;   //Затухание на трассе                            19
    //Помеха
    double SppBase;     //Спектральная плотность мощности помехи         20
    double delFp;   //Эффективная ширина спектра помехи              21
    double GpNoise; //Макимальный КУ антенны САП                     22
    double Apom;    //Уровень нормированной ДН РЛС в направлении САП 23
    double gammaPNoise;//Расхождение поляризаций антенн РЛС и САП    24
    double DpBase;      //Дальность САП в режиме помеха прикрытия        25
    //Разведприемник
    double Rp;      //Дальность разведприемника                      26
    double GpRec;   //КУ антенны                                     27
    double Arp;     //Уровень нормированной ДН РЛС в направлении РП  28
    double Nshr;    //КШ приемника                                   29
    double Do;      //ВПО                                            30
    double FpRec;   //ВЛТ                                            31
    double delFpRec;//Ширина ПП приемника                            32
    double TpRec;   //Время интегрирования                           33
    double ro;      //Коэффициент энергетических потерь              34
    double gammaPRec;//Расхождение поляризаций антенн РЛС и РП       35

    double lambdaRls;
    
    double delfpri;
    double delfprlcm;
    double dekl;
    
    double delFpei;
    double delFpelcm;
    double delFpefkm;

    const double kb = 1.38*std::pow(10, -23); //Постоянная Больцмана
    const double T = 273; //Абсолютная температура
    
    double delfshi;
    double Psh;
    double Tn;
    double N;
    double Tc_imp;
    double Tc_lchm;
    double tc_fkm;
    double Tc_fkm;

    double B_imp;
    double B_lchm;
    double B_fkm;

    double K_p_imp;
    double K_p_lchm;
    double K_p_fkm;
};

#endif // CALCULATORWIDGET_H