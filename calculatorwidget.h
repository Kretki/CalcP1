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

#include <math.h>
#include <vector>
#include <cmath>

#include <QDebug>

#include <QWidget>
#include <QVBoxLayout>
#include <QPen>
#include <QScrollArea>
#include <QWheelEvent>
#include <QLabel>
#include <QFrame>
#include <iostream>
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
    void combine_results();
private:
    void receive_base_data();
    void prob_true_discover_graphics(QVBoxLayout* wrapper_layout);
    void noise_eff_coefficient_graphics(QVBoxLayout* wrapper_layout);
    void self_defense_prob_true_discover_graphics(QVBoxLayout* wrapper_layout);
    void self_defense_noise_eff_coefficient_graphics(QVBoxLayout* wrapper_layout);
    void hide_evaluation_discovery_distance(QVBoxLayout* wrapper_layout);
    void hide_evaluation_proba_discovery(QVBoxLayout* wrapper_layout);
    void hide_evaluation_from_power(QVBoxLayout* wrapper_layout);

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

    // double k_imp_eff_act_noise_self_defence(double Dp, double Spp);
    // double k_lchm_eff_act_noise_self_defence(double Dp, double Spp);
    // double k_fkm_eff_act_noise_self_defence(double Dp, double Spp);

    double k_imp_eff_imp(double Dp, double Spp);
    double k_imp_eff_lchm(double Dp, double Spp);
    double k_imp_eff_fkm (double Dp, double Spp);

    double P_c_min_imp();
    double P_c_min_fkm();
    double P_c_min_lchm();

    double R_c_u(double Pi);
    double R_c_fkm(double Pi);
    double  R_c_lchm(double Pi);

    double P_prm (double Pi, double Rp); //мощность сигнала на входе энергетического приемника

    double P_sr_imp(double Pi, double Rp); //сред мощность полезного сигнала
    double P_sr_fkm(double Pi, double Rp);
    double P_sr_lchm(double Pi, double Rp);

    double q_csh_imp(double Pi,  double Rp ) ;      //отношение сигнал - шум
    double q_csh_fkm(double Pi,  double Rp ) ;
    double q_csh_lchm(double Pi,  double Rp ) ;

    double ar (double x); //обратная функция ошибок

    double D_p_imp(double Pi,  double Rp ) ;
    double D_p_fkm(double Pi,  double Rp ) ;
    double D_p_lchm(double Pi,  double Rp ) ;

    double q_0_out(); //отнош сигнал/шум для достижениие заданной вероятности прав обнаруж Do и ложной тревоги Fp в разведприемнике
    double n_imp();
    double n_fkm();
    double n_lchm();

    double k_imp();
    double k_fkm();
    double k_lchm();

    double q_0_out_imp(); //отношение сигнал/шум на входе энергетического приемника
    double q_0_out_fkm();
    double q_0_out_lchm();

    double P_p_min_imp(); //чувствительность энергетического разведприемника
    double P_p_min_fkm();
    double P_p_min_lchm();

    double R_p_imp(double Pi);  //дальность обнаружения РЛС разведприемником
    double R_p_fkm(double Pi);
    double R_p_lchm(double Pi);

    //коэффициент скрытности
    //R_c_i(P) - дальность обнаружения цели РЛ станцией
    //R_p_u (Pi) -дальность обнаружения РЛС разведприемником

    double S_imp(double Pi);
    double S_fkm(double Pi);
    double S_lchm(double Pi);

    double Q_fkm();       //Скважность  ФКМ сигнала
    double Q_imp();   //Скважность импульсного сигнала
    double Q_lchm();  //Скважность ЛЧМ


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
    QwtPlot* graph_10_plot;
    QwtPlot* graph_11_plot;
    QwtPlot* graph_12_plot;
    QwtPlot* graph_13_plot;
    QwtPlot* graph_14_plot;
    QwtPlot* graph_15_plot;
    QwtPlot* graph_16_plot;

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
    double tc_fkm;
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
    double delfprfkm;//dekl;
    
    double delFpei;
    double delFpelcm;
    double delFpefkm;

    const double kb = 1.38*std::pow(10, -23); //Постоянная Больцмана
    const double T = 273; //Абсолютная температура
    
    double delfshi;
    double Psh;
    double Tn;
    // double N;
    double Tc_imp;
    double Tc_lchm;
    // double tc_fkm;
    double Tc_fkm;

    double B_imp;
    double B_lchm;
    double B_fkm;

    double K_p_imp;
    double K_p_lchm;
    double K_p_fkm;

    double q_min = 31.219; //минимальное отношение сигнал шум для РЛС
    double P_psh = 5.651* pow(10, -14); // мощность собственных щшумов разведприёмника

    double eta=3.142*pow (10, 4); // параметр временного накопления
    double x=1-FpRec;
    double N; //число импульсов в пачке (стр. 11)
};

#endif // CALCULATORWIDGET_H
