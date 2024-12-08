#include "calculatorwidget.h"
QwtPlotZoom::QwtPlotZoom(QWidget *parent, double* l_in_min, double* l_in_max, double* l_in_step, double* b_in_min, double* b_in_max, double* b_in_step) : QwtPlot(parent) 
{
    l_min = new double(0.0);
    l_max = new double(1.0);
    b_min = new double(0.0);
    b_max = new double(1.0);

    if(l_in_min)
    {
        delete l_min;
        l_min = l_in_min;
    }
    if(l_in_max)
    {
        delete l_max;
        l_max = l_in_max;
    }
    l_step = new double((*l_max - *l_min)/5);
    if(l_in_step)
        l_step = l_in_step;
    if(b_in_min)
    {
        delete b_min;
        b_min = b_in_min;
    }
    if(b_in_max)
    {
        delete b_max;
        b_max = b_in_max;
    }
    b_step = new double((*b_max - *b_min)/5);
    if(b_in_step)
        b_step = b_in_step;
     
    this->setAxisScale( QwtPlot::yLeft, *l_min, *l_max, *l_step);
    this->setAxisScale( QwtPlot::xBottom, *b_min, *b_max, *b_step);

    zoomer = new QwtPlotZoomer(canvas());
    zoomer->setRubberBand(QwtPicker::RectRubberBand);
    zoomer->setRubberBandPen(QPen(Qt::red, 2));
    zoomer->setTrackerMode(QwtPicker::AlwaysOn);
    zoomer->setAxes( QwtPlot::xBottom, QwtPlot::yLeft );
    zoomer->setZoomBase();
}

QwtPlotZoom::~QwtPlotZoom()
{
    delete l_min;
    delete l_max;
    delete l_step;
    delete b_min;
    delete b_max;
    delete b_step;
};

void QwtPlotZoom::wheelEvent(QWheelEvent *event)
{
    const int zoomFactor = 2;
    if (event->angleDelta().y() > 0)
    {
        zoomer->zoom(zoomFactor);
    }
    else
    {
        zoomer->zoom(-zoomFactor);
    }
    event->accept();
}

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
}

CalculatorWidget::~CalculatorWidget()
{
    delete layout;
    delete vars;
}

void CalculatorWidget::receive_base_data()
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
    tc_imp = vars->at(12);   //Длительность импульсного сигнала               12
    tc_lchm = vars->at(13);   //Длительность ЛЧМ сигнала                       13
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
    delfpri = 1/tc_imp; // Импульсный сигнал    
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
    Tc_imp = tc_imp*N;

    Tc_lchm = tc_lchm*N;;

    tc_fkm = Tpsig/Q;
    Tc_fkm = tc_fkm*N;
}

void CalculatorWidget::prob_true_discover_graphics()
{
    graph_1_plot = new QwtPlotZoom(this, nullptr, nullptr, nullptr, nullptr, new double(20000.0), new double(5000.0));
    // graph_1_plot = new QwtPlot(this);
    graph_1_plot->setTitle( "Зависимость вероятности правильного обнаружения от дальности до цели" );
    graph_1_plot->setCanvasBackground( Qt::white );
    graph_1_plot->setAxisTitle( QwtPlot::yLeft, "Вероятность правильного обнаружения" );
    graph_1_plot->setAxisTitle( QwtPlot::xBottom, "Дальность до цели, м" );
    // graph_1_plot->setAxisScale( QwtPlot::yLeft, 0.0, 1.0 );
    // graph_1_plot->setAxisScale( QwtPlot::xBottom, 0.0, 20000.0, 5000.0 );
    graph_1_plot->insertLegend( new QwtLegend() );


    QwtPlotGrid* grid_1 = new QwtPlotGrid();
    grid_1->attach( graph_1_plot );

    scrollLayout->addWidget(graph_1_plot);

    // graph_2_plot = new QwtPlot(this);
    graph_2_plot = new QwtPlotZoom(this, new double(0.0001), new double(0.000101), nullptr, nullptr, new double(100000.0), new double(20000.0));
    graph_2_plot->setTitle( "Зависимость вероятности правильного обнаружения от дальности до цели (режим прикрытие)" );
    graph_2_plot->setCanvasBackground( Qt::white );
    graph_2_plot->setAxisTitle( QwtPlot::yLeft, "Вероятность правильного обнаружения" );
    graph_2_plot->setAxisTitle( QwtPlot::xBottom, "Дальность помехи, м" );
    // graph_2_plot->setAxisScale( QwtPlot::yLeft, 0.0001, 0.000101 );
    // graph_2_plot->setAxisScale( QwtPlot::xBottom, 0.0, 100000.0, 20000.0 );
    graph_2_plot->insertLegend( new QwtLegend() );

    
    QwtPlotGrid* grid_2 = new QwtPlotGrid();
    grid_2->attach( graph_2_plot );

    scrollLayout->addWidget(graph_2_plot);

    // graph_3_plot = new QwtPlot(this);
    graph_3_plot = new QwtPlotZoom(this, new double(std::pow(10, -4)), new double(1.05*std::pow(10, -4)), nullptr, nullptr, new double(std::pow(10, -4)), new double(2*std::pow(10, -5)));
    graph_3_plot->setTitle( "Зависимость характеристики обнаружения то спекртральной плотности мощности помехи" );
    graph_3_plot->setCanvasBackground( Qt::white );
    graph_3_plot->setAxisTitle( QwtPlot::yLeft, "Вероятность правильного обнаружения" );
    graph_3_plot->setAxisTitle( QwtPlot::xBottom, "Спектральная плотность мощности помехи, Вт/Гц" );
    // graph_3_plot->setAxisScale( QwtPlot::yLeft, 0.0001, 0.00010015 );
    // graph_3_plot->setAxisScale( QwtPlot::xBottom, 0.0, 0.0001, 0.00002 );
    graph_3_plot->insertLegend( new QwtLegend() );


    QwtPlotGrid* grid_3 = new QwtPlotGrid();
    grid_3->attach( graph_3_plot );

    scrollLayout->addWidget(graph_3_plot);


    //Рисуем зависимость вероятности правильного обнаружения от дальности до цели
    QwtPlotCurve* curve_imp_1 = new QwtPlotCurve();
    curve_imp_1->setTitle( "Импульсный сигнал" );
    curve_imp_1->setPen( QPen( Qt::blue, 4 ) ),
    curve_imp_1->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_lchm_1 = new QwtPlotCurve();
    curve_lchm_1->setTitle( "ЛЧМ сигнал" );
    curve_lchm_1->setPen( QPen( Qt::green, 4 ) ),
    curve_lchm_1->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_fkm_1 = new QwtPlotCurve();
    curve_fkm_1->setTitle( "ФКМ сигнал" );
    curve_fkm_1->setPen( QPen( Qt::red, 4 ) ),
    curve_fkm_1->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    // QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse, QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    // curve_imp->setSymbol( symbol );

    QPolygonF points_imp;
    QPolygonF points_lchm;
    QPolygonF points_fkm;

    for(int i = 0; i<20000; i+=10)
    {
        points_imp << QPointF(i, this->D_imp(i, DpBase, SppBase));
        points_lchm << QPointF(i, this->D_lchm(i, DpBase, SppBase));
        points_fkm << QPointF(i, this->D_fkm(i, DpBase, SppBase));
    }
    curve_imp_1->setSamples(points_imp);
    curve_imp_1->attach(graph_1_plot);

    curve_lchm_1->setSamples(points_lchm);
    curve_lchm_1->attach(graph_1_plot);

    curve_fkm_1->setSamples(points_fkm);
    curve_fkm_1->attach(graph_1_plot);

    //Рисуем зависимость вероятности правильного обнаружения от дальности до цели (режим прикрытие)
    points_imp.clear();
    points_lchm.clear();
    points_fkm.clear();

    QwtPlotCurve* curve_imp_2 = new QwtPlotCurve();
    curve_imp_2->setTitle( "Импульсный сигнал" );
    curve_imp_2->setPen( QPen( Qt::blue, 4 ) ),
    curve_imp_2->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_lchm_2 = new QwtPlotCurve();
    curve_lchm_2->setTitle( "ЛЧМ сигнал" );
    curve_lchm_2->setPen( QPen( Qt::green, 4 ) ),
    curve_lchm_2->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_fkm_2 = new QwtPlotCurve();
    curve_fkm_2->setTitle( "ФКМ сигнал" );
    curve_fkm_2->setPen( QPen( Qt::red, 4 ) ),
    curve_fkm_2->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    for(int i = 0; i<110000; i+=1000)
    {
        points_imp << QPointF(i, this->D_imp(50000, i, SppBase));
        points_lchm << QPointF(i, this->D_lchm(50000, i, SppBase));
        points_fkm << QPointF(i, this->D_fkm(50000, i, SppBase));
    }
    curve_imp_2->setSamples(points_imp);
    curve_imp_2->attach(graph_2_plot);

    curve_lchm_2->setSamples(points_lchm);
    curve_lchm_2->attach(graph_2_plot);

    curve_fkm_2->setSamples(points_fkm);
    curve_fkm_2->attach(graph_2_plot);

    //Рисуем зависимость характеристики обнаружения от спектральной плотности мощности помехи
    points_imp.clear();
    points_lchm.clear();
    points_fkm.clear();

    QwtPlotCurve* curve_imp_3 = new QwtPlotCurve();
    curve_imp_3->setTitle( "Импульсный сигнал" );
    curve_imp_3->setPen( QPen( Qt::blue, 4 ) ),
    curve_imp_3->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_lchm_3 = new QwtPlotCurve();
    curve_lchm_3->setTitle( "ЛЧМ сигнал" );
    curve_lchm_3->setPen( QPen( Qt::green, 4 ) ),
    curve_lchm_3->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_fkm_3 = new QwtPlotCurve();
    curve_fkm_3->setTitle( "ФКМ сигнал" );
    curve_fkm_3->setPen( QPen( Qt::red, 4 ) ),
    curve_fkm_3->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    for(double i = 0; i<0.00011; i+=0.000001)
    {
        points_imp << QPointF(i, this->D_imp(50000, DpBase, i));
        points_lchm << QPointF(i, this->D_lchm(50000, DpBase, i));
        points_fkm << QPointF(i, this->D_fkm(50000, DpBase, i));
    }
    curve_imp_3->setSamples(points_imp);
    curve_imp_3->attach(graph_3_plot);

    curve_lchm_3->setSamples(points_lchm);
    curve_lchm_3->attach(graph_3_plot);

    curve_fkm_3->setSamples(points_fkm);
    curve_fkm_3->attach(graph_3_plot);
}

void CalculatorWidget::noise_eff_coefficient_graphics()
{
    // graph_4_plot = new QwtPlot(this);
    graph_4_plot = new QwtPlotZoom(this, nullptr, new double(4*std::pow(10, 6)), nullptr, nullptr, new double(std::pow(10, 5)), new double(2*std::pow(10, 4)));
    graph_4_plot->setTitle( "Зависимость зоны подавления РЛС от дальности до цели" );
    graph_4_plot->setCanvasBackground( Qt::white );
    graph_4_plot->setAxisTitle( QwtPlot::yLeft, "Коэффициент эффективности помехи" );
    graph_4_plot->setAxisTitle( QwtPlot::xBottom, "Дальность цели, м" );
    // graph_4_plot->setAxisScale( QwtPlot::yLeft, 0, 4*std::pow(10, 6), std::pow(10, 6) );
    // graph_4_plot->setAxisScale( QwtPlot::xBottom, 0.0, std::pow(10, 5), 2*std::pow(10, 4) );
    graph_4_plot->insertLegend( new QwtLegend() );


    QwtPlotGrid* grid_4 = new QwtPlotGrid();
    grid_4->attach( graph_4_plot );

    scrollLayout->addWidget(graph_4_plot);

    // graph_5_plot = new QwtPlot(this);
    graph_5_plot = new QwtPlotZoom(this, nullptr, new double(6*std::pow(10, 8)), nullptr, nullptr, new double(4*std::pow(10, 4)), new double(std::pow(10, 4)));
    graph_5_plot->setTitle( "Зависимость зоны подавления РЛС от дальности помехи" );
    graph_5_plot->setCanvasBackground( Qt::white );
    graph_5_plot->setAxisTitle( QwtPlot::yLeft, "Коэффициент эффективности помехи" );
    graph_5_plot->setAxisTitle( QwtPlot::xBottom, "Дальность помехи, м" );
    // graph_5_plot->setAxisScale( QwtPlot::yLeft, 0, 6*std::pow(10, 8), 2*std::pow(10, 8) );
    // graph_5_plot->setAxisScale( QwtPlot::xBottom, 0.0, 4*std::pow(10, 4), 1*std::pow(10, 4) );
    graph_5_plot->insertLegend( new QwtLegend() );


    QwtPlotGrid* grid_5 = new QwtPlotGrid();
    grid_5->attach( graph_5_plot );

    scrollLayout->addWidget(graph_5_plot);

    // graph_6_plot = new QwtPlot(this);
    graph_6_plot = new QwtPlotZoom(this, nullptr, new double(5*std::pow(10, 7)), nullptr, nullptr, new double(std::pow(10, -4)), new double(2*std::pow(10, -5)));
    graph_6_plot->setTitle( "Зависимость зоны подавления РЛС от спектральной плотности помехи" );
    graph_6_plot->setCanvasBackground( Qt::white );
    graph_6_plot->setAxisTitle( QwtPlot::yLeft, "Коэффициент эффективности помехи" );
    graph_6_plot->setAxisTitle( QwtPlot::xBottom, "Спектральная плотность помехи, Вт/Гц" );
    // graph_6_plot->setAxisScale( QwtPlot::yLeft, 0, 5*std::pow(10, 7), std::pow(10, 7) );
    // graph_6_plot->setAxisScale( QwtPlot::xBottom, 0.0, std::pow(10, -4), 2*std::pow(10, -5) );
    graph_6_plot->insertLegend( new QwtLegend() );


    QwtPlotGrid* grid_6 = new QwtPlotGrid();
    grid_6->attach( graph_6_plot );

    scrollLayout->addWidget(graph_6_plot);


    //Базы сигналов
    B_imp = delfpri*tc_imp;
    B_lchm = delfpri*tc_lchm;
    B_fkm = delfpri*tc_fkm;

    K_p_imp = N*B_imp/(log10(1/Fc)/log10(1/Dpor)-1);
    K_p_lchm = N*B_lchm/(log10(1/Fc)/log10(1/Dpor)-1);
    K_p_fkm = N*B_fkm/(log10(1/Fc)/log10(1/Dpor)-1);
    
    //Рисуем зависимость коэффициента эффективности помехи от дальности цели
    QPolygonF points_imp;
    QPolygonF points_lchm;
    QPolygonF points_fkm;

    QwtPlotCurve* curve_imp_4 = new QwtPlotCurve();
    curve_imp_4->setTitle( "Импульсный сигнал" );
    curve_imp_4->setPen( QPen( Qt::blue, 4 ) ),
    curve_imp_4->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_lchm_4 = new QwtPlotCurve();
    curve_lchm_4->setTitle( "ЛЧМ сигнал" );
    curve_lchm_4->setPen( QPen( Qt::green, 4 ) ),
    curve_lchm_4->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_fkm_4 = new QwtPlotCurve();
    curve_fkm_4->setTitle( "ФКМ сигнал" );
    curve_fkm_4->setPen( QPen( Qt::red, 4 ) ),
    curve_fkm_4->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    for(int i = 0; i<std::pow(10, 5); i+=std::pow(10, 3))
    {
        points_imp << QPointF(i, this->k_imp_eff_act_noise(i, DpBase, SppBase));
        points_lchm << QPointF(i, this->k_lchm_eff_act_noise(i, DpBase, SppBase));
        points_fkm << QPointF(i, this->k_fkm_eff_act_noise(i, DpBase, SppBase));
    }

    curve_imp_4->setSamples(points_imp);
    curve_imp_4->attach(graph_4_plot);

    curve_lchm_4->setSamples(points_lchm);
    curve_lchm_4->attach(graph_4_plot);

    curve_fkm_4->setSamples(points_fkm);
    curve_fkm_4->attach(graph_4_plot);

    //Рисуем зависимость коэффициента эффективности помехи от дальности помехи
    points_imp.clear();
    points_lchm.clear();
    points_fkm.clear();

    QwtPlotCurve* curve_imp_5 = new QwtPlotCurve();
    curve_imp_5->setTitle( "Импульсный сигнал" );
    curve_imp_5->setPen( QPen( Qt::blue, 4 ) ),
    curve_imp_5->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_lchm_5 = new QwtPlotCurve();
    curve_lchm_5->setTitle( "ЛЧМ сигнал" );
    curve_lchm_5->setPen( QPen( Qt::green, 4 ) ),
    curve_lchm_5->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_fkm_5 = new QwtPlotCurve();
    curve_fkm_5->setTitle( "ФКМ сигнал" );
    curve_fkm_5->setPen( QPen( Qt::red, 4 ) ),
    curve_fkm_5->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    for(int i = 0; i<4*std::pow(10, 4); i+=5*std::pow(10, 2))
    {
        points_imp << QPointF(i, this->k_imp_eff_act_noise(50000, i, SppBase));
        points_lchm << QPointF(i, this->k_lchm_eff_act_noise(50000, i, SppBase));
        points_fkm << QPointF(i, this->k_fkm_eff_act_noise(50000, i, SppBase));
    }

    curve_imp_5->setSamples(points_imp);
    curve_imp_5->attach(graph_5_plot);

    curve_lchm_5->setSamples(points_lchm);
    curve_lchm_5->attach(graph_5_plot);

    curve_fkm_5->setSamples(points_fkm);
    curve_fkm_5->attach(graph_5_plot);

    //Рисуем зависимость коэффициента эффективности помехи от спектральной плотности помехи
    points_imp.clear();
    points_lchm.clear();
    points_fkm.clear();

    QwtPlotCurve* curve_imp_6 = new QwtPlotCurve();
    curve_imp_6->setTitle( "Импульсный сигнал" );
    curve_imp_6->setPen( QPen( Qt::blue, 4 ) ),
    curve_imp_6->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_lchm_6 = new QwtPlotCurve();
    curve_lchm_6->setTitle( "ЛЧМ сигнал" );
    curve_lchm_6->setPen( QPen( Qt::green, 4 ) ),
    curve_lchm_6->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_fkm_6 = new QwtPlotCurve();
    curve_fkm_6->setTitle( "ФКМ сигнал" );
    curve_fkm_6->setPen( QPen( Qt::red, 4 ) ),
    curve_fkm_6->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    for(double i = 0; i<std::pow(10, -4); i+=std::pow(10, -6))
    {
        points_imp << QPointF(i, this->k_imp_eff_act_noise(50000, DpBase, i));
        points_lchm << QPointF(i, this->k_lchm_eff_act_noise(50000, DpBase, i));
        points_fkm << QPointF(i, this->k_fkm_eff_act_noise(50000, DpBase, i));
    }

    curve_imp_6->setSamples(points_imp);
    curve_imp_6->attach(graph_6_plot);

    curve_lchm_6->setSamples(points_lchm);
    curve_lchm_6->attach(graph_6_plot);

    curve_fkm_6->setSamples(points_fkm);
    curve_fkm_6->attach(graph_6_plot);
}

void CalculatorWidget::self_defense_prob_true_discover_graphics()
{
    //Рисуем зависимость вероятности правильного обнаружения цели от дальности цели и помехи
    // graph_7_plot = new QwtPlot(this);
    graph_7_plot = new QwtPlotZoom(this, new double(std::pow(10, -4)), new double(std::pow(10, -3)), nullptr, nullptr, new double(8*std::pow(10, 4)), nullptr);
    graph_7_plot->setTitle( "Зависимость вероятности правильного обнаружения цели от дальности цели и помехи" );
    graph_7_plot->setCanvasBackground( Qt::white );
    graph_7_plot->setAxisTitle( QwtPlot::yLeft, "Вероятность правильного обнаружения" );
    graph_7_plot->setAxisTitle( QwtPlot::xBottom, "Дальность до цели и помехи, м" );
    // graph_7_plot->setAxisScale( QwtPlot::yLeft, std::pow(10, -4), 1.6*std::pow(10, -4), 2*std::pow(10, -5) );
    // graph_7_plot->setAxisScale( QwtPlot::xBottom, 0.0, 2*std::pow(10, 4), 4*std::pow(10, 3) );
    graph_7_plot->insertLegend( new QwtLegend() );


    QwtPlotGrid* grid_7 = new QwtPlotGrid();
    grid_7->attach( graph_7_plot );

    scrollLayout->addWidget(graph_7_plot);


    QPolygonF points_imp;
    QPolygonF points_lchm;
    QPolygonF points_fkm;

    QwtPlotCurve* curve_imp_7 = new QwtPlotCurve();
    curve_imp_7->setTitle( "Импульсный сигнал" );
    curve_imp_7->setPen( QPen( Qt::blue, 4 ) ),
    curve_imp_7->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_lchm_7 = new QwtPlotCurve();
    curve_lchm_7->setTitle( "ЛЧМ сигнал" );
    curve_lchm_7->setPen( QPen( Qt::green, 4 ) ),
    curve_lchm_7->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_fkm_7 = new QwtPlotCurve();
    curve_fkm_7->setTitle( "ФКМ сигнал" );
    curve_fkm_7->setPen( QPen( Qt::red, 4 ) ),
    curve_fkm_7->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    for(int i = 0; i<8*std::pow(10, 4); i+=std::pow(10, 2))
    {
        points_imp << QPointF(i, this->D_imp_self_defense(i, SppBase));
        points_lchm << QPointF(i, this->D_lchm_self_defense(i, SppBase));
        points_fkm << QPointF(i, this->D_fkm_self_defense(i, SppBase));
    }

    curve_imp_7->setSamples(points_imp);
    curve_imp_7->attach(graph_7_plot);

    curve_lchm_7->setSamples(points_lchm);
    curve_lchm_7->attach(graph_7_plot);

    curve_fkm_7->setSamples(points_fkm);
    curve_fkm_7->attach(graph_7_plot);

    //Рисуем зависимость вероятности правильного обнаружения цели от спектральной плотности помехи
    // graph_8_plot = new QwtPlot(this);
    graph_8_plot = new QwtPlotZoom(this, new double(std::pow(10, -4)), new double(1.01*std::pow(10, -4)), nullptr, nullptr, new double(std::pow(10, -4)), nullptr);
    graph_8_plot->setTitle( "Зависимость вероятности правильного обнаружения цели от спектральной плотности помехи" );
    graph_8_plot->setCanvasBackground( Qt::white );
    graph_8_plot->setAxisTitle( QwtPlot::yLeft, "Вероятность правильного обнаружения" );
    graph_8_plot->setAxisTitle( QwtPlot::xBottom, "Спектральная плотность мощности помехи, Вт/Гц" );
    // graph_8_plot->setAxisScale( QwtPlot::yLeft, std::pow(10, -4), 1.01*std::pow(10, -4), std::pow(10, -7) );
    // graph_8_plot->setAxisScale( QwtPlot::xBottom, 0.0, std::pow(10, -4), 2*std::pow(10, -5) );
    graph_8_plot->insertLegend( new QwtLegend() );


    QwtPlotGrid* grid_8 = new QwtPlotGrid();
    grid_8->attach( graph_8_plot );

    scrollLayout->addWidget(graph_8_plot);


    points_imp.clear();
    points_lchm.clear();
    points_fkm.clear();

    QwtPlotCurve* curve_imp_8 = new QwtPlotCurve();
    curve_imp_8->setTitle( "Импульсный сигнал" );
    curve_imp_8->setPen( QPen( Qt::blue, 4 ) ),
    curve_imp_8->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_lchm_8 = new QwtPlotCurve();
    curve_lchm_8->setTitle( "ЛЧМ сигнал" );
    curve_lchm_8->setPen( QPen( Qt::green, 4 ) ),
    curve_lchm_8->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_fkm_8 = new QwtPlotCurve();
    curve_fkm_8->setTitle( "ФКМ сигнал" );
    curve_fkm_8->setPen( QPen( Qt::red, 4 ) ),
    curve_fkm_8->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    for(double i = 0; i<std::pow(10, -4); i+=std::pow(10, -7))
    {
        points_imp << QPointF(i, this->D_imp_self_defense(DpBase, i));
        points_lchm << QPointF(i, this->D_lchm_self_defense(DpBase, i));
        points_fkm << QPointF(i, this->D_fkm_self_defense(DpBase, i));
    }

    curve_imp_8->setSamples(points_imp);
    curve_imp_8->attach(graph_8_plot);

    curve_lchm_8->setSamples(points_lchm);
    curve_lchm_8->attach(graph_8_plot);

    curve_fkm_8->setSamples(points_fkm);
    curve_fkm_8->attach(graph_8_plot);
}

void CalculatorWidget::self_defense_noise_eff_coefficient_graphics()
{

}

void CalculatorWidget::calculate()
{
    this->receive_base_data();
    this->prob_true_discover_graphics();
    this->noise_eff_coefficient_graphics();
    this->self_defense_prob_true_discover_graphics();
}