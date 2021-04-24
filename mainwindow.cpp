#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <unistd.h>
#include <QString>
#include "qcustomplot.h"
#include <QtWidgets>
#include <QThread>
#include <QFont>
#include "wiringPi.h"
#include <QLCDNumber>
#include <QTime>
#include <QTimer>


#define PIN_NUM 27



MainWindow::MainWindow(QWidget *parent) :
//     QLCDNumber(parent),
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{

QPixmap bg("/home/pi/qtCode/background.png");

QPalette p(palette());
p.setBrush(QPalette::Background, bg);

setAutoFillBackground(true);
setPalette(p);

ui->setupUi(this);
//raspberrypi setting--------------------------------------
gpio_interrupt=false;
//    pinMode(PIN_NUM, OUTPUT);

QTimer *timer = new QTimer(this);
connect(timer, SIGNAL(timeout()), this, SLOT(digital_clock()));
timer->start(1000);
setupPins();
//---------------------------------------------------------digital clock
//    setSegmentStyle(QLCDNumber::Filled);

//    QTimer *timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, &MainWindow::showTime);
//    timer->start(1000);

//    showTime();

//    setWindowTitle(tr("Digital Clock"));
//    resize(150, 60);
    //------------------------------------------------------------
    proc = new QProcess(this);
    proc2 = new QProcess(this);
    connect(proc, SIGNAL(started()), this, SLOT(verifyStatus()));
    connect(proc, SIGNAL(finished(int)), this, SLOT(readResult()));
    connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(readResult()));
    connect(proc,SIGNAL(readyReadStandardError()),this,SLOT(readyReadStandardError()));
    //    ping->setProcessChannelMode(QProcess::MergedChannels);
//--------------------------------------------------------------------------------------scope
    setscope();
    setguage();

    //-----------------------------------------------------------------------guage



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digital_clock()
{
    QTime t;
    ui->lcdNumber->setDigitCount(8);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber->setStyleSheet("color: green;"
                                 "background-color: white");

    ui->lcdNumber->display(t.currentTime().toString());
  }

void MainWindow::showTime()
{
//    QTime time = QTime::currentTime();
//    QString text = time.toString("hh:mm");
//    if ((time.second() % 2) == 0)
//        text[2] = ' ';
//    display(text);
}

void MainWindow::setscope(){
    QFont font;
    font.setPointSize(21);
    font.setItalic(true);
    font.setBold(true);
//    ui->label_adc_data->setFont(font);
//    ui->label_adc_data->setAlignment(Qt::AlignCenter);
//    ui->label_adc_data->setStyleSheet("background-color : white; color : green;");

    /* Configure setup for Thank You Label */
//    ui->label_ty->setAlignment(Qt::AlignCenter);
//    ui->label_ty->setStyleSheet("background-color : white; color : black;");

    /* Align the intro label appropriately */
//    ui->label_intro->setAlignment(Qt::AlignCenter);
//    ui->label_intro->setStyleSheet("background-color : white; color : black;");

    /* Thread to continously sample and read the data */
//    QThread *thread = new QThread;
//    AD7190 *ad7190_dev = new AD7190();
//    ad7190_dev->moveToThread(thread);
//    connect(thread,SIGNAL(started()),ad7190_dev,SLOT(AD7190_init_thread()));
//    connect(ad7190_dev, SIGNAL(new_adc_data(ulong)),this,SLOT(display_data(ulong)));
//    thread->start();

    /* Add graph and set the curve line color to green */
    ui->CustomPlot->addGraph();
    ui->CustomPlot->graph(0)->setPen(QPen(Qt::red));
    ui->CustomPlot->graph(0)->setAntialiasedFill(false);
    ui->CustomPlot->addGraph();
    ui->CustomPlot->graph(1)->setPen(QPen(Qt::blue));
    ui->CustomPlot->graph(1)->setAntialiasedFill(false);
    ui->CustomPlot->addGraph();
    ui->CustomPlot->graph(2)->setPen(QPen(Qt::green));
    ui->CustomPlot->graph(2)->setAntialiasedFill(false);

    /* Configure x-Axis as time in secs */
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s");
    ui->CustomPlot->xAxis->setTicker(timeTicker);
    ui->CustomPlot->axisRect()->setupFullAxesBox();


    /* Configure x and y-Axis to display Labels */
    ui->CustomPlot->xAxis->setTickLabelFont(QFont(QFont().family(),8));
    ui->CustomPlot->yAxis->setTickLabelFont(QFont(QFont().family(),8));
    ui->CustomPlot->xAxis->setLabel("Time(s)");
    ui->CustomPlot->yAxis->setLabel("ADC Raw Counts");

    /* Make top and right axis visible, but without ticks and label */
    ui->CustomPlot->xAxis2->setVisible(true);
    ui->CustomPlot->yAxis->setVisible(true);
    ui->CustomPlot->xAxis2->setTicks(false);
    ui->CustomPlot->yAxis2->setTicks(false);
    ui->CustomPlot->xAxis2->setTickLabels(false);
    ui->CustomPlot->yAxis2->setTickLabels(false);

    /* Set up and initialize the graph plotting timer */
    connect(&timer_plot, SIGNAL(timeout()),this,SLOT(realtimePlot()));
    timer_plot.start(5);
}
void MainWindow::setguage(){

    mSpeedGauge = new QcGaugeWidget;
    mSpeedGauge->addBackground(99);
    QcBackgroundItem *bkg1 = mSpeedGauge->addBackground(92);
    bkg1->clearrColors();
    bkg1->addColor(0.1,Qt::black);
    bkg1->addColor(1.0,Qt::white);

    QcBackgroundItem *bkg2 = mSpeedGauge->addBackground(88);
    bkg2->clearrColors();
    bkg2->addColor(0.1,Qt::gray);
    bkg2->addColor(1.0,Qt::darkGray);

    mSpeedGauge->addArc(55);
    mSpeedGauge->addDegrees(65)->setValueRange(0,80);
    mSpeedGauge->addColorBand(50);

    mSpeedGauge->addValues(80)->setValueRange(0,80);

    mSpeedGauge->addLabel(70)->setText("Km/h");
    QcLabelItem *lab = mSpeedGauge->addLabel(40);
    lab->setText("0");
    mSpeedNeedle = mSpeedGauge->addNeedle(60);
    mSpeedNeedle->setLabel(lab);
    mSpeedNeedle->setColor(Qt::white);
    mSpeedNeedle->setValueRange(0,80);
    mSpeedGauge->addBackground(7);
    mSpeedGauge->addGlass(88);
    ui->verticalLayout->addWidget(mSpeedGauge);
}

void MainWindow::verifyStatus(){
    if(proc->isReadable()){
        qDebug() << "read on ...";
        connect(proc, SIGNAL(readyRead()), this, SLOT(readResult()));
        if(proc->canReadLine()){
            qDebug() << "LINE read on ...";
        }
    }else{
        qDebug() << "not able to read ...";
    }
}

void MainWindow::readResult(){
    running = false;
    qDebug() <<  proc->readAllStandardOutput();
}

void MainWindow::start_command(){
    if(proc){
//        QByteArray command("224\r");
 //proc->setInputChannelMode( QProcess::ForwardedInputChannel );
//        QString command = "ping";
//        QStringList args;
//        args << "-w" <<  "3" <<  "www.google.com";

//        proc->start(command, argu);
        sleep(0.5);
       // proc->write("224-2/./pass.sh",argu);
        //proc->write("224\n");\n");
//        argu<<"";
//        proc->start("/home/e224-2/./ptpcmd.sh",argu);
//          proc->waitForStarted(3000);
       // proc->write(command);
    //    proc2->start("/home/e224
     //   running = true;
//        proc->waitForFinished(5000);
    }
    else
    {
        qDebug()<<"There is no process";
    }
}

bool MainWindow::is_running(){
    return running;
}

bool MainWindow::finished(){
    //proc->terminate();
    return proc->atEnd();
}






void MainWindow::readyReadStandardError()
{
   qDebug() << Q_FUNC_INFO;
   qDebug() << proc->readAllStandardError();
}

//void MainWindow::on_pushButton_5_clicked() //add button
//{

//    addPoint(ui->bx_x->value(),ui->vx_y->value());
//    plot();
//}
//------------------------------------------------------------------------------------------scope

void MainWindow::display_data(unsigned long adc_data)
{
    /* Discard the noisy bits */
//    adc_data = adc_data/100;
    static unsigned int cnt=0;
    adc_data=cnt; cnt++;
    /* Support the plotter */
    adc_data_g = adc_data;

    /* Prepare to display the data */
    QString adc_data_str = " ";
    adc_data_str = QString::number(adc_data);

}

/****************************************************************
 * Function Name : realtimePlot
 * Description   : Displays the real time graph on the GUI
 * Returns       : None
 * Params        : None
 ****************************************************************/
void MainWindow::realtimePlot()
{
    static QTime t1= (QTime::currentTime());
    double key = t1.elapsed()/100.0; // smaller then more fast
    static double lastPointKey = 0;
    static bool Toggled=0;
    static double current_val=0;
    //static double cnt=0;

    if(key - lastPointKey > 0.05)
    {

        if(gpio_interrupt==true)
        {
            qDebug() <<"interrupt at realtime";
            gpio_interrupt=false;
            if(digitalRead(29)==1)
            {
                //                val_spgauage+=2;
                ui->CustomPlot->graph(0)->addData(key, 3);
                current_val=3;
            }
            else
            {
                //                val_spgauage-=2;
                ui->CustomPlot->graph(0)->addData(key, 0);
                current_val=0;
            }
        }
        else
        {
             ui->CustomPlot->graph(0)->addData(key, current_val);
        }
//        ui->CustomPlot->graph(0)->addData(key, val_spgauage);
//        adc_data_g=10;
//        if(Toggled) {ui->CustomPlot->graph(0)->addData(key, (double)adc_data_g+2); Toggled=0;}
//        else {ui->CustomPlot->graph(0)->addData(key, (double)adc_data_g-2); Toggled=1;}


        //ui->CustomPlot->graph(0)->addData(key, (double)adc_data_g);
        //        ui->CustomPlot->graph(1)->addData(key, (double)adc_data_g+2);
        //        ui->CustomPlot->graph(2)->addData(key, (double)adc_data_g-2);
        lastPointKey = key;
    }

    /* make key axis range scroll right with the data at a constant range of 8. */

    ui->CustomPlot->graph(0)->rescaleValueAxis(); //key is changing continously
    ui->CustomPlot->xAxis->setRange(key, 15, Qt::AlignRight);
    ui->CustomPlot->yAxis->setRange(0, 15, Qt::AlignCenter); // set yaxis fixed
    ui->CustomPlot->replot();
}

void MainWindow::on_ToggleButton_clicked()
{
    qDebug("Button pressed");

    if (state) {
        state = 0;
         digitalWrite(27, LOW);
    } else {
        state = 1;
        digitalWrite(27, HIGH);
    }

}

void MainWindow::setupPins()
{
    wiringPiSetup();
    //PIN GPIO.0 as output
    system("gpio mode 27 out"); //mode uses WiringPi pin notation
    pinMode(27,OUTPUT);
    pinMode(29,INPUT);
//    system("gpio export 27 out"); //export uses BCM pin notation
// system("gpio export 29 in");
    //PIN GPIO.7 as input, pullup resistor activated
//    system("gpio mode 28 in");
//    system("gpio mode 28 up");
//    system("gpio export 28 in");

    //Call WiringPi initialization
//    wiringPiSetupSys();

    connect(this, SIGNAL(Interrupt_SIG()),this,SLOT(realtimePlot()));

    qDebug("Pins setup finalized");

}

void MainWindow::interrupt()
{
    gpio_interrupt=true;
    Interrupt_SIG();
    qDebug("ISR called");

}
/****************************************************************
 * Function Name : on_pushButton_released
 * Description   : Displays THANK YOU! when pressed and released
 * Returns       : None
 * Params        : None
 ****************************************************************/



//-------------------------------------------------------------------------------------------------------

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    val_spgauage=value;
    mSpeedNeedle->setCurrentValue(value);
}


void MainWindow::on_pushButton_clicked()
{
    //        QByteArray command("224\r");
     //proc->setInputChannelMode( QProcess::ForwardedInputChannel );
            QString command = "sudo ptp4l";
            QStringList args;
            args << "-i eth0 -S -P -m -2" ;

            qDebug()<< command << args;
            proc->start("/home/pi/qtCode/ptp_cmd.sh");
//            QProcess::execute("/home/pi/qtCode/ptp_cmd.sh");
//            proc->start(command, args);
//            sleep(0.5);
           // proc->write("224-2/./pass.sh",argu);
            //proc->write("224\n");\n");
    //        argu<<"";
    //        proc->start("/home/e224-2/./ptpcmd.sh",argu);
    //          proc->waitForStarted(3000);
           // proc->write(command);
        //    proc2->start("/home/e224
         //   running = true;
    //        proc->waitForFinished(5000);
}
