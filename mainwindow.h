#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "mergesort.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();

    void on_randomButton_clicked();

private:
    Ui::MainWindow *ui;
    int *arr;
    size_t size;
    QGraphicsScene *scene;
    QGraphicsRectItem *rectangle;

    mergesort* sort;
};
#endif // MAINWINDOW_H
