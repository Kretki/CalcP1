#include "calculatorwidget.h"

CalculatorWidget::CalculatorWidget(std::array<double, 36>* vars, QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    this->setLayout(layout);

    scrollWidg = new QWidget(this);
    scrollLayout = new QVBoxLayout(scrollWidg);
    scrollWidg->setLayout(scrollLayout);
    scrollWidg->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea = new QScrollArea();
    scrollArea->setWidget(scrollWidg);
    scrollArea->setWidgetResizable(true);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(scrollArea, 1);

    this->vars = vars;

    plot = new QwtPlot(this);
    plot->setTitle( "Зависимость вероятности правильного обнаружения от дальности до цели" );
    plot->setCanvasBackground( Qt::white );
    plot->setAxisScale( QwtPlot::yLeft, 0.0, 1.0 );
    plot->setAxisScale( QwtPlot::xBottom, 0.0, 20000.0, 5000.0 );
    plot->insertLegend( new QwtLegend() );

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->attach( plot );

    scrollLayout->addWidget(plot);
}

CalculatorWidget::~CalculatorWidget()
{
    delete layout;
    delete vars;
}

void CalculatorWidget::calculate()
{

    Pi = vars->at(0);      //Импульсная мощность РЛС                        0
    Gc = vars->at(1);      //КУ антенны                                     1
    Nsh = vars->at(2);     //КШ приемника                                   2
    fc = vars->at(3);      //Рабочая частота                                3
    Fc = vars->at(4);      //ВЛТ                                            4
    Dpor = vars->at(5);    //Пороговая вероятность обнаружения              5
    delR = vars->at(6);    //Разрешающая способность по дальности           6
    delVr = vars->at(7);   //Разрешающая способность по скорости            7
    // Сигнал и обработка
    c = vars->at(8);       //Скорость света                                 8
    Fpsig = vars->at(9);   //Частота повторения                             9
    Tpsig = vars->at(10);   //Период повторения                              10
    Tk = vars->at(11);      //Время контакта с целью                         11
    tcimp = vars->at(12);   //Длительность импульсного сигнала               12
    tclcm = vars->at(13);   //Длительность ЛЧМ сигнала                       13
    W = vars->at(14);       //Девиация                                       14
    tkv = vars->at(15);     //Длительность ФМ кванта                         15
    Q = vars->at(16);       //Скважность                                     16
    // Цель и трасса
    eprc = vars->at(17);    //ЭПР цели                                       17
    DcBase = vars->at(18);      //Дальность цели                                 18
    alpha = vars->at(19);   //Затухание на трассе                            19
    // Помеха
    SppBase = vars->at(20);     //Спектральная плотность мощности помехи         20
    delFp = vars->at(21);   //Эффективная ширина спектра помехи              21
    GpNoise = vars->at(22); //Макимальный КУ антенны САП                     22
    Apom = vars->at(23);    //Уровень нормированной ДН РЛС в направлении САП 23
    gammaPNoise = vars->at(24);//Расхождение поляризаций антенн РЛС и САП    24
    DpBase = vars->at(25);      //Дальность САП в режиме помеха прикрытия        25
    // Разведприемник
    Rp = vars->at(26);      //Дальность разведприемника                      26
    GpRec = vars->at(27);   //КУ антенны                                     27
    Arp = vars->at(28);     //Уровень нормированной ДН РЛС в направлении РП  28
    Nshr = vars->at(29);    //КШ приемника                                   29
    Do = vars->at(30);      //ВПО                                            30
    FpRec = vars->at(31);   //ВЛТ                                            31
    delFpRec = vars->at(32);//Ширина ПП приемника                            32
    TpRec = vars->at(33);   //Время интегрирования                           33
    ro = vars->at(34);      //Коэффициент энергетических потерь              34
    gammaPRec = vars->at(35);//Расхождение поляризаций антенн РЛС и РП       35
    //Длина волны РЛС
    lambdaRls = c/fc;
    // Ширина ПП приемника подавляемой РЛС
    delfpri = 1/tcimp; // Импульсный сигнал    
    delfprlcm = W; //ЛЧМ сигнал
    dekl = 1/tkv; //ФКМ сигнал
    //delfpr < delFp для всех типов зондирующих сигналов => 
    //Эквивалентная полоса помехового сигнала
    delFpei = delfpri; // Импульсный сигнал
    delFpelcm = delfprlcm; //ЛЧМ сигнал
    delFpefkm = dekl; //ФКМ сигнал

    delfshi = delfpri; //Эквивалентная шумовая полоса приемника

    Psh = kb*T*delfshi*Nsh; //Мощность собственных шумов приемного устройства в полосе пропускания линейной части приемника
    Tn = lambdaRls/(2*delVr); //Время накопления импульсов
    //Так как Tn<Tk
    Tn = Tk;
    N = Tn/Tpsig; //Число импульсов в пачке
    Tc_imp = tcimp*N;

    Tc_lchm = tclcm*N;;

    tc_fkm = Tpsig/Q;
    Tc_fkm = tc_fkm*N;

    //Рисуем зависимость вероятности правильного обнаружения от дальности до цели

    QwtPlotCurve* curve_imp = new QwtPlotCurve();
    curve_imp->setTitle( "Импульсный сигнал" );
    curve_imp->setPen( QPen( Qt::blue, 4 ) ),
    curve_imp->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_lchm = new QwtPlotCurve();
    curve_lchm->setTitle( "ЛЧМ сигнал" );
    curve_lchm->setPen( QPen( Qt::green, 4 ) ),
    curve_lchm->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_fkm = new QwtPlotCurve();
    curve_fkm->setTitle( "ФКМ сигнал" );
    curve_fkm->setPen( QPen( Qt::red, 4 ) ),
    curve_fkm->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    // QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse, QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    // curve_imp->setSymbol( symbol );

    QPolygonF points_imp;
    QPolygonF points_lchm;
    QPolygonF points_fkm;

    for(int i = 0; i<20000; i+=100)
    {
        points_imp << QPointF(i, this->D_imp(i, DpBase, SppBase));
        points_lchm << QPointF(i, this->D_lchm(i, DpBase, SppBase));
        points_fkm << QPointF(i, this->D_fkm(i, DpBase, SppBase));
    }
    curve_imp->setSamples(points_imp);
    curve_imp->attach(plot);

    curve_lchm->setSamples(points_lchm);
    curve_lchm->attach(plot);

    curve_fkm->setSamples(points_fkm);
    curve_fkm->attach(plot);
}

// double CalculatorWidget::Pc(double Dc)
// {
//     return 
// }