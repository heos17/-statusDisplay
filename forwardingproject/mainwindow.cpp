#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QPixmap bg("./background.png");

    QPalette p(palette());
    p.setBrush(QPalette::Window, bg);

    setAutoFillBackground(true);
    setPalette(p);

    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

