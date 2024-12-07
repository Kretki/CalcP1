#include "calculatorwidget.h"

double CalculatorWidget::P_c(double Dc)
{
    //Мощность полезного сигнала
    return Pi*Gc/(4*M_PI*std::pow(Dc, 2))*eprc/(4*M_PI*std::pow(Dc, 2))*Gc*std::pow(lambdaRls, 2)/(4*M_PI)*std::pow(10, -0.2*alpha*Dc);
}

double CalculatorWidget::P_pp_imp(double Spp)
{
    //Мощность передатчика помех импульсного сигнала
    return Spp*this->delFpei;
}

double CalculatorWidget::P_p_imp(double Dp, double Spp)
{
    //Мощность сигнала постановщика помех на входе приемника для импульсного сигнала
    return P_pp_imp(Spp)*this->GpNoise/(4*M_PI*std::pow(Dp, 2))*Gc*std::pow(lambdaRls, 2)/(4*M_PI)*std::pow(Apom, 2)*gammaPNoise*std::pow(10, -0.1*alpha*Dp);
}


double CalculatorWidget::q_imp(double Dc, double Dp, double Spp)
{
    //Отношение сигнал/шум для импульсного сигнала
    return P_c(Dc)/(this->Psh+P_p_imp(Dp, Spp))*2*Tc_imp*delfpri;
}

double CalculatorWidget::D_imp(double Dc, double Dp, double Spp)
{
    //Вероятность правильного обнаружения для импульсного сигнала
    return std::pow(Fc, 1/(1+q_imp(Dc, Dp, Spp)/2));
}

double CalculatorWidget::P_pp_lchm(double Spp)
{
    //Мощность передатчика помех ЛЧМ сигнала
    return Spp*this->delFpelcm;
}

double CalculatorWidget::P_p_lchm(double Dp, double Spp)
{
    //Мощность сигнала постановщика помех на входе приемника для ЛЧМ сигнала
    return P_pp_lchm(Spp)*this->GpNoise/(4*M_PI*std::pow(Dp, 2))*Gc*std::pow(lambdaRls, 2)/(4*M_PI)*std::pow(Apom, 2)*gammaPNoise*std::pow(10, -0.1*alpha*Dp);
}


double CalculatorWidget::q_lchm(double Dc, double Dp, double Spp)
{
    //Отношение сигнал/шум для ЛЧМ сигнала
    return P_c(Dc)/(this->Psh+P_p_lchm(Dp, Spp))*2*Tc_lchm*delfprlcm;
}

double CalculatorWidget::D_lchm(double Dc, double Dp, double Spp)
{
    //Вероятность правильного обнаружения для ЛЧМ сигнала
    return std::pow(Fc, 1/(1+q_lchm(Dc, Dp, Spp)/2));
}

double CalculatorWidget::P_pp_fkm(double Spp)
{
    //Мощность передатчика помех ФКМ сигнала
    return Spp*this->delFpefkm;
}

double CalculatorWidget::P_p_fkm(double Dp, double Spp)
{
    //Мощность сигнала постановщика помех на входе приемника для ЛЧМ сигнала
    return P_pp_fkm(Spp)*this->GpNoise/(4*M_PI*std::pow(Dp, 2))*Gc*std::pow(lambdaRls, 2)/(4*M_PI)*std::pow(Apom, 2)*gammaPNoise*std::pow(10, -0.1*alpha*Dp);
}

double CalculatorWidget::q_fkm(double Dc, double Dp, double Spp)
{
    //Отношение сигнал/шум для ЛЧМ сигнала
    return P_c(Dc)/(this->Psh+P_p_fkm(Dp, Spp))*2*Tc_fkm*dekl;
}

double CalculatorWidget::D_fkm(double Dc, double Dp, double Spp)
{
    //Вероятность правильного обнаружения для ЛЧМ сигнала
    return std::pow(Fc, 1/(1+q_fkm(Dc, Dp, Spp)/2));
}

double CalculatorWidget::k_imp_eff_act_noise(double Dc, double Dp, double Spp)
{
    //Коэффициент эффективности помехи импульсного сигнала (отношение мощности активной помехи к мощности сигнала на входе приемника РЛС)
    return P_pp_imp(Spp)*this->GpNoise*(4*M_PI*std::pow(Dc, 4))/(Pi*Gc*eprc*std::pow(Dp, 2))*std::pow(Apom, 2)*delfpri/delFp*gammaPNoise*std::pow(10, 0.1*alpha*(2*Dc-Dp));
}

double CalculatorWidget::k_lchm_eff_act_noise(double Dc, double Dp, double Spp)
{
    //Коэффициент эффективности помехи ЛЧМ сигнала (отношение мощности активной помехи к мощности сигнала на входе приемника РЛС)
    return P_pp_lchm(Spp)*this->GpNoise*(4*M_PI*std::pow(Dc, 4))/(Pi*Gc*eprc*std::pow(Dp, 2))*std::pow(Apom, 2)*delfprlcm/delFp*gammaPNoise*std::pow(10, 0.1*alpha*(2*Dc-Dp));
}

double CalculatorWidget::k_fkm_eff_act_noise(double Dc, double Dp, double Spp)
{
    //Коэффициент эффективности помехи ФКМ сигнала (отношение мощности активной помехи к мощности сигнала на входе приемника РЛС)
    return P_pp_fkm(Spp)*this->GpNoise*(4*M_PI*std::pow(Dc, 4))/(Pi*Gc*eprc*std::pow(Dp, 2))*std::pow(Apom, 2)*dekl/delFp*gammaPNoise*std::pow(10, 0.1*alpha*(2*Dc-Dp));
}