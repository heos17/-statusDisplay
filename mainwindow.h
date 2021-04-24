#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTimer>
#include <QTime>
#include "qcgaugewidget.h"
#include <QLCDNumber>


#include "/home/j/rasp/sysroot/usr/include/wiringPi.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow //, public QLCDNumber
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void start_command();
    bool is_running();
    bool finished();
    void addPoint(double x, double y);
    void clearData();
    void plot();

    void setupPins();
    void interrupt();


signals:
    void Interrupt_SIG();
public slots:
    void digital_clock();
    void verifyStatus();
    void readResult();
    void readyReadStandardError();

    void setscope();
    void setguage();
    void display_data(unsigned long adc_data);
    void realtimePlot();

    void on_horizontalSlider_valueChanged(int value);

private slots:

    void on_ToggleButton_clicked();

     void showTime();
     void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QProcess *proc;
    QProcess *proc2;
    QString command;
    QStringList argu;
    QVector<double> x,y;
    bool running;

    unsigned long adc_data_g;
    QTimer timer_plot;



    QcGaugeWidget * mSpeedGauge;
    QcNeedleItem *mSpeedNeedle;

    double val_spgauage;
    QTime time;
    int state;
    int num;

    bool gpio_interrupt;
};

#endif // MAINWINDOW_H
