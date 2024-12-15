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
    return P_c(Dc)/(this->Psh+P_p_fkm(Dp, Spp))*2*Tc_fkm*delfprfkm;
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
    return P_pp_fkm(Spp)*this->GpNoise*(4*M_PI*std::pow(Dc, 4))/(Pi*Gc*eprc*std::pow(Dp, 2))*std::pow(Apom, 2)*delfprfkm/delFp*gammaPNoise*std::pow(10, 0.1*alpha*(2*Dc-Dp));
}


double CalculatorWidget::P_c_self_defense(double Dp)
{
    return Pi*Gc/(4*M_PI*std::pow(Dp, 2))*eprc/(4*M_PI*std::pow(Dp, 2))*Gc*std::pow(lambdaRls, 2)/(4*M_PI)*std::pow(10, -0.2*alpha*Dp);
}

double CalculatorWidget::P_p_imp_self_defense(double Dp, double Spp)
{
    return P_pp_imp(Spp)*GpNoise/(4*M_PI*std::pow(Dp, 2))*Gc*std::pow(lambdaRls, 2)/(4*M_PI)*gammaPNoise*std::pow(10, -0.1*alpha*Dp);
}

double CalculatorWidget::P_p_lchm_self_defense(double Dp, double Spp)
{
    return P_pp_lchm(Spp)*GpNoise/(4*M_PI*std::pow(Dp, 2))*Gc*std::pow(lambdaRls, 2)/(4*M_PI)*gammaPNoise*std::pow(10, -0.1*alpha*Dp);
}

double CalculatorWidget::P_p_fkm_self_defense(double Dp, double Spp)
{
    return P_pp_fkm(Spp)*GpNoise/(4*M_PI*std::pow(Dp, 2))*Gc*std::pow(lambdaRls, 2)/(4*M_PI)*gammaPNoise*std::pow(10, -0.1*alpha*Dp);
}

double CalculatorWidget::q_imp_self_defense(double Dp, double Spp)
{
    return P_c_self_defense(Dp)/(Psh+P_p_imp_self_defense(Dp, Spp))*2*Tc_imp*delfpri;
}

double CalculatorWidget::q_lchm_self_defense(double Dp, double Spp)
{
    return P_c_self_defense(Dp)/(Psh+P_p_lchm_self_defense(Dp, Spp))*2*Tc_lchm*delfprlcm;
}

double CalculatorWidget::q_fkm_self_defense(double Dp, double Spp)
{
    return P_c_self_defense(Dp)/(Psh+P_p_fkm_self_defense(Dp, Spp))*2*Tc_fkm*delfprfkm;
}

double CalculatorWidget::D_imp_self_defense(double Dp, double Spp)
{
    return std::pow(Fc, 1/(1+q_imp_self_defense(Dp, Spp)/2));
}

double CalculatorWidget::D_lchm_self_defense(double Dp, double Spp)
{
    return std::pow(Fc, 1/(1+q_lchm_self_defense(Dp, Spp)/2));
}

double CalculatorWidget::D_fkm_self_defense(double Dp, double Spp)
{
    return std::pow(Fc, 1/(1+q_fkm_self_defense(Dp, Spp)/2));
}

// double CalculatorWidget::k_imp_eff_act_noise_self_defence(double Dp, double Spp)
// {
//     //Коэффициент эффективности помехи импульсного сигнала (отношение мощности активной помехи к мощности сигнала на входе приемника РЛС)
//     return P_pp_imp(Spp)*this->GpNoise*(4*M_PI*std::pow(Dp, 2))/(Pi*Gc*eprc)*delfpri/delFp*gammaPNoise*std::pow(10, 0.1*alpha*Dp);
// }

// double CalculatorWidget::k_lchm_eff_act_noise_self_defence(double Dp, double Spp)
// {
//     //Коэффициент эффективности помехи ЛЧМ сигнала (отношение мощности активной помехи к мощности сигнала на входе приемника РЛС)
//     return P_pp_lchm(Spp)*this->GpNoise*(4*M_PI*std::pow(Dp, 2))/(Pi*Gc*eprc)*delfprlcm/delFp*gammaPNoise*std::pow(10, 0.1*alpha*Dp);
// }

// double CalculatorWidget::k_fkm_eff_act_noise_self_defence(double Dp, double Spp)
// {
//     //Коэффициент эффективности помехи ФКМ сигнала (отношение мощности активной помехи к мощности сигнала на входе приемника РЛС)
//     return P_pp_fkm(Spp)*this->GpNoise*(4*M_PI*std::pow(Dp, 2))/(Pi*Gc*eprc)*delfprfkm/delFp*gammaPNoise*std::pow(10, 0.1*alpha*Dp);
// }


//коэффициент эффективности помех
// 2.12 -2.13
double CalculatorWidget::k_imp_eff_imp(double Dp, double Spp)
{

    return (P_pp_imp(Spp)*this->GpNoise*(4*M_PI*std::pow(Dp, 4))/(Pi*Gc*eprc*std::pow(Dp, 2)))*(delfpri/delFp)*gammaPNoise*pow(10, 0.1*alpha*(2*Dp-Dp));
}

double CalculatorWidget::k_imp_eff_lchm(double Dp, double Spp)
{

    return (P_pp_lchm(Spp)*this->GpNoise*(4*M_PI*std::pow(Dp, 4))/(Pi*Gc*eprc*std::pow(Dp, 2)))*(delFpelcm/delFp)*gammaPNoise*std::pow(10, 0.1*alpha*(2*Dp-Dp));
}

double CalculatorWidget::k_imp_eff_fkm(double Dp, double Spp)
{

    return (P_pp_fkm(Spp)*this->GpNoise*(4*M_PI*std::pow(Dp, 4))/(Pi*Gc*eprc*std::pow(Dp, 2)))*(delFpefkm/delFp)*gammaPNoise*std::pow(10, 0.1*alpha*(2*Dp-Dp));
}

// зависимость дальности обнаружения цели РЛС от мощности РЛС: импульсный сигнал, ЛЧМ, ФКМ
//2.15
// чувствительность приемника
double CalculatorWidget:: P_c_min_imp(){
    return q_min*Psh * tc_imp /(2*N*tc_imp);
}
double CalculatorWidget::P_c_min_fkm(){
    return q_min*Psh * tc_fkm /(2*N*tc_fkm);
}
double CalculatorWidget::P_c_min_lchm(){
    return q_min*Psh * tc_lchm /(2*N*tc_lchm);
}

// дальность обнаружения цели РЛС станцией

double CalculatorWidget:: R_c_u(double Pi){
    return pow(Pi*pow(Gc,2)*eprc*pow(lambdaRls,2)/( pow(4*M_PI , 3) *  P_c_min_imp()),0.25);
}
double CalculatorWidget:: R_c_fkm(double Pi){
    return pow(Pi*pow(Gc,2)*eprc*pow(lambdaRls,2)/( pow(4*M_PI , 3) *  P_c_min_fkm()),0.25);
}

double CalculatorWidget:: R_c_lchm(double Pi){
    return pow(Pi*pow(Gc,2)*eprc*pow(lambdaRls,2)/( pow(4*M_PI , 3) *  P_c_min_lchm()),0.25);
}

//мощность сигнала на входе энергетического приемника (без учета потерь)
double CalculatorWidget:: P_prm(double Pi, double Rp){
    return Pi*Gc*GpRec*pow(lambdaRls,2)/( pow(4*M_PI * Rp , 2) );
}



double CalculatorWidget::  Q_fkm(){  //Скважность  ФКМ сигнала
    return Tpsig / tc_fkm;
};
double CalculatorWidget::  Q_imp(){ //Скважность импульсного сигнала
   return Tpsig / tc_imp;
};
double CalculatorWidget::  Q_lchm(){  //Скважность ЛЧМ
   return Tpsig / tc_lchm;
};

//средняя мощность полезного сигнала
double CalculatorWidget:: P_sr_imp(double Pi, double Rp){
    return P_prm(Pi, Rp) / Q_imp();
}
double CalculatorWidget:: P_sr_fkm(double Pi, double Rp){
    return P_prm(Pi, Rp)/ Q_fkm();
}
double CalculatorWidget:: P_sr_lchm(double Pi, double Rp){
    return P_prm(Pi, Rp) / Q_lchm();
}

// отношение сигнал/шум
double  CalculatorWidget::  q_csh_imp(double Pi,  double Rp ) {
    return P_sr_imp(Pi, Rp) / P_psh ;
}
double  CalculatorWidget:: q_csh_fkm(double Pi,  double Rp ) {
    return P_sr_fkm(Pi, Rp) / P_psh ;
}
double  CalculatorWidget:: q_csh_lchm(double Pi,  double Rp ) {
    return P_sr_lchm(Pi, Rp)/ P_psh ;
}

//обратная функция ошибок
double CalculatorWidget:: ar (double x){
    return 0.5 * pow(M_PI, 0.5) *(x + M_PI * pow(x, 3)/12 +7 * pow(M_PI, 2) * pow (x, 5) /480 + 127 * pow(M_PI, 3) * pow(x, 7)/ 40320 + 4369 * pow(M_PI, 4) * pow(x, 9)/ 5806080 + 34807 * pow(M_PI, 5) * pow(x, 11)/ 182476800 );
}

//вероятность правильного обнаружения энергетич приемником излучения РЛС
//double erf_x = erf(x);

double CalculatorWidget:: D_p_imp(double Pi,  double Rp ){
    // return (1 - erf(ar(x) - q_csh_imp(Pi, Rp) * pow(eta/2, 0.5) /(1+q_csh_imp(Pi, Rp)) ));
    return (1 - 1/(pow(2*M_PI,0.5))*erf( (ar(x) - q_csh_imp(Pi, Rp) * pow(eta/2, 0.5)) /(1+q_csh_imp(Pi, Rp)) )) ;
}

double CalculatorWidget:: D_p_fkm(double Pi,  double Rp ){
    // return (1 - erf(ar(x) - q_csh_fkm(Pi, Rp) * pow(eta/2, 0.5) /(1+q_csh_fkm(Pi, Rp)) ));
    return (1 - 1/pow(2*M_PI,0.5)* erf( ( ar(x) - q_csh_fkm(Pi, Rp) * pow(eta/2, 0.5)) /(1+q_csh_fkm(Pi, Rp)) ) );
}

double CalculatorWidget:: D_p_lchm(double Pi,  double Rp ){
    // return (1 - erf(ar(x) - q_csh_lchm(Pi, Rp) * pow(eta/2, 0.5) /(1+q_csh_lchm(Pi, Rp)) ));
    return (1 - 1/(pow(2*M_PI,0.5))* erf( ( ar(x) - q_csh_lchm(Pi, Rp) * pow(eta/2, 0.5)) /(1+q_csh_lchm(Pi, Rp)) ) );
}


//отнош сигнал/шум для достижениие заданной вероятности прав обнаруж Do и ложной тревоги Fp в разведприемнике
double CalculatorWidget:: q_0_out(){
    // return ar(1-FpRec) - ar(1-Do) / (pow(eta/2,0.5) + ar (1-Do));
    return (ar(1-FpRec) - ar(1-Do)) / (pow(eta/2,0.5) + ar (1-Do));
}


double CalculatorWidget::  n_imp(){
    return 2*delfpri*Tc_imp * ro;
}
double CalculatorWidget::  n_fkm(){
     return 2*delfprfkm*Tc_fkm * ro;
}
double CalculatorWidget::  n_lchm(){
    return 2*delfprlcm*Tc_lchm * ro;
}

double CalculatorWidget::  k_imp(){
    return  delFpRec*TpRec*ro / (delfpri*Tc_imp);
}
double  CalculatorWidget::  k_fkm(){
    return  delFpRec*TpRec*ro / (delfprfkm*Tc_fkm);
}
double CalculatorWidget::   k_lchm(){
    return  delFpRec*TpRec*ro / (delfprlcm*Tc_lchm);
}

//отношение сигнал/шум на входе энергетического приемника
double CalculatorWidget:: q_0_out_imp(){
    return (4 * q_0_out() + pow(16 * pow(q_0_out(),2) +  8 *  n_imp() * k_imp() , 0.5)) / (2 *  n_imp());
}
double CalculatorWidget::  q_0_out_fkm(){
   return (4 * q_0_out() + pow(16 * pow(q_0_out(),2) + 8 *  n_fkm() * k_fkm() , 0.5)) / (2 *  n_fkm()) ;
}
double CalculatorWidget:: q_0_out_lchm(){
    return (4 * q_0_out() + pow(16 * pow(q_0_out(),2) + 8 *  n_lchm() * k_lchm() , 0.5)) / (2 *  n_lchm());
}

//чувствительность энергетического разведприемника
double CalculatorWidget:: P_p_min_imp()  {
   return P_psh* q_0_out_imp();
}

double CalculatorWidget:: P_p_min_fkm() {
   return P_psh* q_0_out_fkm() ;
}

double CalculatorWidget:: P_p_min_lchm(){
   return P_psh * q_0_out_lchm() ;
}

//дальность обнаружения РЛС разведприемником
double CalculatorWidget:: R_p_imp(double P){//i){
//    return pow( (Pi*Gc*GpRec * pow(lambdaRls, 2) * gammaPRec * pow(Arp,2) ) /( pow( 4* M_PI, 2) * P_p_min_imp())  , 0.5) ;
    return pow( (P*Gc*GpRec * pow(lambdaRls, 2) * gammaPRec * pow(Arp,2) ) /( pow( 4* M_PI, 2) * P_p_min_imp())  , 0.5) ;
}

double CalculatorWidget:: R_p_fkm(double P){//i){
//    return pow( (Pi*Gc*GpRec * pow(lambdaRls, 2) * gammaPRec * pow(Arp,2) ) /( pow( 4* M_PI, 2) * P_p_min_fkm())  , 0.5) ; ;
    return pow( (P*Gc*GpRec * pow(lambdaRls, 2) * gammaPRec * pow(Arp,2) ) /( pow( 4* M_PI, 2) * P_p_min_fkm())  , 0.5) ; ;
}
double CalculatorWidget::  R_p_lchm(double P){//i){
    // return pow( (Pi*Gc*GpRec * pow(lambdaRls, 2) * gammaPRec * pow(Arp,2) ) /( pow( 4* M_PI, 2) * P_p_min_lchm())  , 0.5) ;;
    return pow( (P*Gc*GpRec * pow(lambdaRls, 2) * gammaPRec * pow(Arp,2) ) /( pow( 4* M_PI, 2) * P_p_min_lchm())  , 0.5) ;;
}
//коэффициент скрытности

double  CalculatorWidget:: S_imp(double P){//i){
//   return R_c_u(Pi)/R_p_imp(Pi);
    return R_c_u(P)/R_p_imp(P);
}

double CalculatorWidget:: S_fkm(double P){//i ){
    // return R_c_fkm(Pi)/R_p_fkm(Pi);
    return R_c_fkm(P)/R_p_fkm(P);
}
double CalculatorWidget::  S_lchm(double P){//i){
    // return R_c_lchm(Pi)/R_p_lchm(Pi);
    return R_c_lchm(P)/R_p_lchm(P);
}