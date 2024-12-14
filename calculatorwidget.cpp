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
    delfprfkm = 1/tkv; //ФКМ сигнал
    //delfpr < delFp для всех типов зондирующих сигналов => 
    //Эквивалентная полоса помехового сигнала
    delFpei = delfpri; // Импульсный сигнал
    delFpelcm = delfprlcm; //ЛЧМ сигнал
    delFpefkm = delfprfkm; //ФКМ сигнал

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

    x = 1-FpRec;
}

void CalculatorWidget::prob_true_discover_graphics(QVBoxLayout* wrapper_layout)
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

    wrapper_layout->addWidget(graph_1_plot);

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

    wrapper_layout->addWidget(graph_2_plot);

    // graph_3_plot = new QwtPlot(this);
    graph_3_plot = new QwtPlotZoom(this, new double(std::pow(10, -4)), new double(1.05*std::pow(10, -4)), nullptr, nullptr, new double(std::pow(10, -4)), new double(2*std::pow(10, -5)));
    graph_3_plot->setTitle( "Зависимость характеристики обнаружения от спекртральной плотности мощности помехи" );
    graph_3_plot->setCanvasBackground( Qt::white );
    graph_3_plot->setAxisTitle( QwtPlot::yLeft, "Вероятность правильного обнаружения" );
    graph_3_plot->setAxisTitle( QwtPlot::xBottom, "Спектральная плотность мощности помехи, Вт/Гц" );
    // graph_3_plot->setAxisScale( QwtPlot::yLeft, 0.0001, 0.00010015 );
    // graph_3_plot->setAxisScale( QwtPlot::xBottom, 0.0, 0.0001, 0.00002 );
    graph_3_plot->insertLegend( new QwtLegend() );


    QwtPlotGrid* grid_3 = new QwtPlotGrid();
    grid_3->attach( graph_3_plot );

    wrapper_layout->addWidget(graph_3_plot);


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

void CalculatorWidget::noise_eff_coefficient_graphics(QVBoxLayout* wrapper_layout)
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

    wrapper_layout->addWidget(graph_4_plot);

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

    wrapper_layout->addWidget(graph_5_plot);

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

    wrapper_layout->addWidget(graph_6_plot);


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

void CalculatorWidget::self_defense_prob_true_discover_graphics(QVBoxLayout* wrapper_layout)
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

    wrapper_layout->addWidget(graph_7_plot);


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

    wrapper_layout->addWidget(graph_8_plot);


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

void CalculatorWidget::self_defense_noise_eff_coefficient_graphics(QVBoxLayout* wrapper_layout)
{
    graph_10_plot = new QwtPlotZoom(this, nullptr, new double(2*std::pow(10, 5)), nullptr, nullptr, new double(4*std::pow(10, 4)), nullptr);
    graph_10_plot->setTitle( "Зависимость зоны подавления РЛС от дальности помехи" );
    graph_10_plot->setCanvasBackground( Qt::white );
    graph_10_plot->setAxisTitle( QwtPlot::yLeft, "Коэффициенты эффективности помехи" );
    graph_10_plot->setAxisTitle( QwtPlot::xBottom, "Дальность помехи, м" );
    graph_10_plot->insertLegend( new QwtLegend() );


    QwtPlotGrid* grid_10 = new QwtPlotGrid();
    grid_10->attach( graph_10_plot );

    wrapper_layout->addWidget(graph_10_plot);


    QPolygonF points_imp;
    QPolygonF points_lchm;
    QPolygonF points_fkm;

    QwtPlotCurve* curve_imp_10 = new QwtPlotCurve();
    curve_imp_10->setTitle( "Импульсный сигнал" );
    curve_imp_10->setPen( QPen( Qt::blue, 4 ) ),
    curve_imp_10->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_lchm_10 = new QwtPlotCurve();
    curve_lchm_10->setTitle( "ЛЧМ сигнал" );
    curve_lchm_10->setPen( QPen( Qt::green, 4 ) ),
    curve_lchm_10->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_fkm_10 = new QwtPlotCurve();
    curve_fkm_10->setTitle( "ФКМ сигнал" );
    curve_fkm_10->setPen( QPen( Qt::red, 4 ) ),
    curve_fkm_10->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    for(int i = 0; i<4*std::pow(10, 4); i+=std::pow(10, 2))
    {
        points_imp << QPointF(i, this->k_imp_eff_imp(i, SppBase));
        points_lchm << QPointF(i, this->k_imp_eff_lchm(i, SppBase));
        points_fkm << QPointF(i, this->k_imp_eff_fkm(i, SppBase));
    }

    curve_imp_10->setSamples(points_imp);
    curve_imp_10->attach(graph_10_plot);

    curve_lchm_10->setSamples(points_lchm);
    curve_lchm_10->attach(graph_10_plot);

    curve_fkm_10->setSamples(points_fkm);
    curve_fkm_10->attach(graph_10_plot);


    graph_11_plot = new QwtPlotZoom(this, nullptr, new double(6*std::pow(10, 7)), nullptr, nullptr, new double(std::pow(10, -4)), nullptr);
    graph_11_plot->setTitle( "Зависимость зоны подавления РЛС от спектральной плотности помехи" );
    graph_11_plot->setCanvasBackground( Qt::white );
    graph_11_plot->setAxisTitle( QwtPlot::yLeft, "Коэффициенты эффективности помехи" );
    graph_11_plot->setAxisTitle( QwtPlot::xBottom, "Спектральная плотность мощности помехи, Вт/Гц" );
    graph_11_plot->insertLegend( new QwtLegend() );


    QwtPlotGrid* grid_11 = new QwtPlotGrid();
    grid_11->attach( graph_11_plot );

    wrapper_layout->addWidget(graph_11_plot);


    points_imp.clear();
    points_lchm.clear();
    points_fkm.clear();

    QwtPlotCurve* curve_imp_11 = new QwtPlotCurve();
    curve_imp_11->setTitle( "Импульсный сигнал" );
    curve_imp_11->setPen( QPen( Qt::blue, 4 ) ),
    curve_imp_11->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_lchm_11 = new QwtPlotCurve();
    curve_lchm_11->setTitle( "ЛЧМ сигнал" );
    curve_lchm_11->setPen( QPen( Qt::green, 4 ) ),
    curve_lchm_11->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_fkm_11 = new QwtPlotCurve();
    curve_fkm_11->setTitle( "ФКМ сигнал" );
    curve_fkm_11->setPen( QPen( Qt::red, 4 ) ),
    curve_fkm_11->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    for(double i = 0; i<std::pow(10, -4); i+=std::pow(10, -6))
    {
        points_imp << QPointF(i, this->k_imp_eff_imp(DpBase, i));
        points_lchm << QPointF(i, this->k_imp_eff_lchm(DpBase, i));
        points_fkm << QPointF(i, this->k_imp_eff_fkm(DpBase, i));
    }

    curve_imp_11->setSamples(points_imp);
    curve_imp_11->attach(graph_11_plot);

    curve_lchm_11->setSamples(points_lchm);
    curve_lchm_11->attach(graph_11_plot);

    curve_fkm_11->setSamples(points_fkm);
    curve_fkm_11->attach(graph_11_plot);
}

void CalculatorWidget::hide_evaluation_discovery_distance(QVBoxLayout* wrapper_layout)
{
    graph_12_plot = new QwtPlotZoom(this, nullptr, new double(8*std::pow(10, 3)), nullptr, nullptr, new double(1*std::pow(10, -2)), nullptr);
    graph_12_plot->setTitle( "Зависимость дальности обнаружения цели РЛ станцией от мощности РЛС" );
    graph_12_plot->setCanvasBackground( Qt::white );
    graph_12_plot->setAxisTitle( QwtPlot::yLeft, "Вероятность правильного обнаружения" );
    graph_12_plot->setAxisTitle( QwtPlot::xBottom, "Мощность сигнала РЛС, Вт" );
    graph_12_plot->insertLegend( new QwtLegend() );


    QwtPlotGrid* grid_12 = new QwtPlotGrid();
    grid_12->attach( graph_12_plot );

    wrapper_layout->addWidget(graph_12_plot);


    QPolygonF points_imp;
    QPolygonF points_lchm;
    QPolygonF points_fkm;

    QwtPlotCurve* curve_imp_12 = new QwtPlotCurve();
    curve_imp_12->setTitle( "Импульсный сигнал" );
    curve_imp_12->setPen( QPen( Qt::blue, 4 ) ),
    curve_imp_12->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_lchm_12 = new QwtPlotCurve();
    curve_lchm_12->setTitle( "ЛЧМ сигнал" );
    curve_lchm_12->setPen( QPen( Qt::green, 4 ) ),
    curve_lchm_12->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_fkm_12 = new QwtPlotCurve();
    curve_fkm_12->setTitle( "ФКМ сигнал" );
    curve_fkm_12->setPen( QPen( Qt::red, 4 ) ),
    curve_fkm_12->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    for(double i = 0; i<std::pow(10, 2); i+=std::pow(10, 0))
    {
        points_imp << QPointF(i, this->P_sr_imp(i, std::pow(10, -4)));
        points_lchm << QPointF(i, this->P_sr_lchm(i, std::pow(10, -4)));
        points_fkm << QPointF(i, this->P_sr_fkm(i, std::pow(10, -4)));
    }

    curve_imp_12->setSamples(points_imp);
    curve_imp_12->attach(graph_12_plot);

    curve_lchm_12->setSamples(points_lchm);
    curve_lchm_12->attach(graph_12_plot);

    curve_fkm_12->setSamples(points_fkm);
    curve_fkm_12->attach(graph_12_plot);

    graph_13_plot = new QwtPlotZoom(this, nullptr, new double(2*std::pow(10, 0)), nullptr, nullptr, new double(1*std::pow(10, -4)), nullptr);
    graph_13_plot->setTitle( "Зависимость дальности обнаружения РЛС разведприемником от дальности разведприемника" );
    graph_13_plot->setCanvasBackground( Qt::white );
    graph_13_plot->setAxisTitle( QwtPlot::yLeft, "Вероятность правильного обнаружения" );
    graph_13_plot->setAxisTitle( QwtPlot::xBottom, "Мощность сигнала РЛС, Вт" );
    graph_13_plot->insertLegend( new QwtLegend() );


    QwtPlotGrid* grid_13 = new QwtPlotGrid();
    grid_13->attach( graph_13_plot );

    wrapper_layout->addWidget(graph_13_plot);


    points_imp.clear();
    points_lchm.clear();
    points_fkm.clear();

    QwtPlotCurve* curve_imp_13 = new QwtPlotCurve();
    curve_imp_13->setTitle( "Импульсный сигнал" );
    curve_imp_13->setPen( QPen( Qt::blue, 4 ) ),
    curve_imp_13->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_lchm_13 = new QwtPlotCurve();
    curve_lchm_13->setTitle( "ЛЧМ сигнал" );
    curve_lchm_13->setPen( QPen( Qt::green, 4 ) ),
    curve_lchm_13->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_fkm_13 = new QwtPlotCurve();
    curve_fkm_13->setTitle( "ФКМ сигнал" );
    curve_fkm_13->setPen( QPen( Qt::red, 4 ) ),
    curve_fkm_13->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    for(double i = 0; i<std::pow(10, -4); i+=std::pow(10, -6))
    {
        points_imp << QPointF(i, this->P_sr_imp(0.01, i));
        points_lchm << QPointF(i, this->P_sr_lchm(0.01, i));
        points_fkm << QPointF(i, this->P_sr_fkm(0.01, i));
    }

    curve_imp_13->setSamples(points_imp);
    curve_imp_13->attach(graph_13_plot);

    curve_lchm_13->setSamples(points_lchm);
    curve_lchm_13->attach(graph_13_plot);

    curve_fkm_13->setSamples(points_fkm);
    curve_fkm_13->attach(graph_13_plot);
}

void CalculatorWidget::hide_evaluation_proba_discovery(QVBoxLayout* wrapper_layout)
{
    graph_14_plot = new QwtPlotZoom(this, nullptr, new double(2*std::pow(10, 0)), nullptr, nullptr, new double(5*std::pow(10, -2)), nullptr);
    graph_14_plot->setTitle( "Зависимость вероятности правильного обнаружения цели от дальности цели и помехи" );
    graph_14_plot->setCanvasBackground( Qt::white );
    graph_14_plot->setAxisTitle( QwtPlot::yLeft, "Вероятность правильного обнаружения" );
    graph_14_plot->setAxisTitle( QwtPlot::xBottom, "Мощность РЛС, Вт" );
    graph_14_plot->insertLegend( new QwtLegend() );


    QwtPlotGrid* grid_14 = new QwtPlotGrid();
    grid_14->attach( graph_14_plot );

    wrapper_layout->addWidget(graph_14_plot);


    QPolygonF points_imp;
    QPolygonF points_lchm;
    QPolygonF points_fkm;

    QwtPlotCurve* curve_imp_14 = new QwtPlotCurve();
    curve_imp_14->setTitle( "Импульсный сигнал" );
    curve_imp_14->setPen( QPen( Qt::blue, 4 ) ),
    curve_imp_14->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_lchm_14 = new QwtPlotCurve();
    curve_lchm_14->setTitle( "ЛЧМ сигнал" );
    curve_lchm_14->setPen( QPen( Qt::green, 4 ) ),
    curve_lchm_14->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve* curve_fkm_14 = new QwtPlotCurve();
    curve_fkm_14->setTitle( "ФКМ сигнал" );
    curve_fkm_14->setPen( QPen( Qt::red, 4 ) ),
    curve_fkm_14->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    for(double i = 0; i<5*std::pow(10, -2); i+=std::pow(10, 4))
    {
        points_imp << QPointF(i, this->D_p_imp(i, SppBase));
        points_lchm << QPointF(i, this->D_p_lchm(i, SppBase));
        points_fkm << QPointF(i, this->D_p_fkm(i, SppBase));
    }

    curve_imp_14->setSamples(points_imp);
    curve_imp_14->attach(graph_14_plot);

    curve_lchm_14->setSamples(points_lchm);
    curve_lchm_14->attach(graph_14_plot);

    curve_fkm_14->setSamples(points_fkm);
    curve_fkm_14->attach(graph_14_plot);
}

void CalculatorWidget::hide_evaluation_from_power(QVBoxLayout* wrapper_layout)
{
    
}

void CalculatorWidget::combine_results()
{
    this->receive_base_data();
    
    QLabel* title_0 = new QLabel(this);
    title_0->setStyleSheet("QLabel { font-size: 25px; font-weight: bold; }");
    title_0->setText("Основные соотношения");
    title_0->setAlignment(Qt::AlignCenter);
    scrollLayout->addWidget(title_0);

    QFrame* line_0 = new QFrame(this);
    line_0->setFrameShape(QFrame::HLine);
    scrollLayout->addWidget(line_0);

    QWidget* wrapper_widget_0 = new QWidget(this);
    QVBoxLayout* wrapper_layout_0 = new QVBoxLayout(wrapper_widget_0);
    wrapper_widget_0->setLayout(wrapper_layout_0);

    this->prob_true_discover_graphics(wrapper_layout_0);

    scrollLayout->addWidget(wrapper_widget_0);

    QFrame* line_1 = new QFrame(this);
    line_1->setFrameShape(QFrame::HLine);
    scrollLayout->addWidget(line_1);

    QLabel* title_1 = new QLabel(this);
    title_1->setStyleSheet("QLabel { font-size: 25px; font-weight: bold; }");
    title_1->setText("Оценка помехоустойчивости");
    title_1->setAlignment(Qt::AlignCenter);
    scrollLayout->addWidget(title_1);

    QFrame* line_2 = new QFrame(this);
    line_2->setFrameShape(QFrame::HLine);
    scrollLayout->addWidget(line_2);

    QWidget* wrapper_widget_1 = new QWidget(this);
    QVBoxLayout* wrapper_layout_1 = new QVBoxLayout(wrapper_widget_1);
    wrapper_widget_1->setLayout(wrapper_layout_1);

    this->noise_eff_coefficient_graphics(wrapper_layout_1);

    scrollLayout->addWidget(wrapper_widget_1);

    QFrame* line_3 = new QFrame(this);
    line_3->setFrameShape(QFrame::HLine);
    scrollLayout->addWidget(line_3);

    QLabel* title_2 = new QLabel(this);
    title_2->setStyleSheet("QLabel { font-size: 25px; font-weight: bold; }");
    title_2->setText("Режим самозащита");
    title_2->setAlignment(Qt::AlignCenter);
    scrollLayout->addWidget(title_2);

    QFrame* line_4 = new QFrame(this);
    line_4->setFrameShape(QFrame::HLine);
    scrollLayout->addWidget(line_4);

    QWidget* wrapper_widget_2 = new QWidget(this);
    QVBoxLayout* wrapper_layout_2 = new QVBoxLayout(wrapper_widget_2);
    wrapper_widget_2->setLayout(wrapper_layout_2);

    this->self_defense_prob_true_discover_graphics(wrapper_layout_2);

    scrollLayout->addWidget(wrapper_widget_2);

    QFrame* line_5 = new QFrame(this);
    line_5->setFrameShape(QFrame::HLine);
    scrollLayout->addWidget(line_5);

    QLabel* title_3 = new QLabel(this);
    title_3->setStyleSheet("QLabel { font-size: 25px; font-weight: bold; }");
    title_3->setText("Оценка помехоустойчивости в режиме самозащиты");
    title_3->setAlignment(Qt::AlignCenter);
    scrollLayout->addWidget(title_3);

    QFrame* line_6 = new QFrame(this);
    line_6->setFrameShape(QFrame::HLine);
    scrollLayout->addWidget(line_6);

    QWidget* wrapper_widget_3 = new QWidget(this);
    QVBoxLayout* wrapper_layout_3 = new QVBoxLayout(wrapper_widget_3);
    wrapper_widget_3->setLayout(wrapper_layout_3);

    this->self_defense_noise_eff_coefficient_graphics(wrapper_layout_3);

    scrollLayout->addWidget(wrapper_widget_3);

    QFrame* line_7 = new QFrame(this);
    line_7->setFrameShape(QFrame::HLine);
    scrollLayout->addWidget(line_7);

    QLabel* title_4 = new QLabel(this);
    title_4->setStyleSheet("QLabel { font-size: 25px; font-weight: bold; }");
    title_4->setText("Зависимость дальности обнаружения\nцели РЛ станцией");
    title_4->setAlignment(Qt::AlignCenter);
    scrollLayout->addWidget(title_4);

    QFrame* line_8 = new QFrame(this);
    line_8->setFrameShape(QFrame::HLine);
    scrollLayout->addWidget(line_8);

    QWidget* wrapper_widget_4 = new QWidget(this);
    QVBoxLayout* wrapper_layout_4 = new QVBoxLayout(wrapper_widget_4);
    wrapper_widget_4->setLayout(wrapper_layout_4);

    this->hide_evaluation_discovery_distance(wrapper_layout_4);

    scrollLayout->addWidget(wrapper_widget_4);

    QFrame* line_9 = new QFrame(this);
    line_9->setFrameShape(QFrame::HLine);
    scrollLayout->addWidget(line_9);

    QLabel* title_5 = new QLabel(this);
    title_5->setStyleSheet("QLabel { font-size: 25px; font-weight: bold; }");
    title_5->setText("Зависимость дальности обнаружения РЛС\nразведприемником от мощности сигнала РЛС");
    title_5->setAlignment(Qt::AlignCenter);
    scrollLayout->addWidget(title_5);

    QFrame* line_10 = new QFrame(this);
    line_10->setFrameShape(QFrame::HLine);
    scrollLayout->addWidget(line_10);

    QWidget* wrapper_widget_5 = new QWidget(this);
    QVBoxLayout* wrapper_layout_5 = new QVBoxLayout(wrapper_widget_5);
    wrapper_widget_5->setLayout(wrapper_layout_5);

    this->hide_evaluation_proba_discovery(wrapper_layout_5);

    scrollLayout->addWidget(wrapper_widget_5);

    QFrame* line_11 = new QFrame(this);
    line_11->setFrameShape(QFrame::HLine);
    scrollLayout->addWidget(line_11);

    QLabel* title_6 = new QLabel(this);
    title_6->setStyleSheet("QLabel { font-size: 25px; font-weight: bold; }");
    title_6->setText("Зависимость дальности обнаружения РЛС\nразведприемником от мощности РЛС\nЗависимость коэффициента скрытности\nот мощности РЛС");
    title_6->setAlignment(Qt::AlignCenter);
    scrollLayout->addWidget(title_6);

    QFrame* line_12 = new QFrame(this);
    line_12->setFrameShape(QFrame::HLine);
    scrollLayout->addWidget(line_12);

    QWidget* wrapper_widget_6 = new QWidget(this);
    QVBoxLayout* wrapper_layout_6 = new QVBoxLayout(wrapper_widget_6);
    wrapper_widget_6->setLayout(wrapper_layout_6);

    this->hide_evaluation_proba_discovery(wrapper_layout_6);

    scrollLayout->addWidget(wrapper_widget_6);
}