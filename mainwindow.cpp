#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    size = 256;
    arr = new int [size];
    scene = new QGraphicsScene();
    for(size_t i = 0; i < size; ++i) {
        arr[i] = std::rand()/((RAND_MAX + 1u)/180);
    }

    ui->graphicsView->setScene(scene);

    sort = new mergesort(scene, arr);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startButton_clicked()
{
    ui->randomButton->setEnabled(false);
    sort->sort();
    ui->randomButton->setEnabled(true);
}

void MainWindow::on_randomButton_clicked()
{
    for(size_t i = 0; i < size; ++i) {
        arr[i] = std::rand()/((RAND_MAX + 1u)/180);
    }
    sort->updateArr(arr);

}
