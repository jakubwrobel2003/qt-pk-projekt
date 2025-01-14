#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "App.h"
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_START_clicked();
    void on_STOP_clicked();

    void on_pushButton_clicked();

    void on_ODCZYT_clicked();
    void updateChart();
    void on_RESET_clicked();

    void on_BTNSETA_clicked();

    void on_BTNSETB_clicked();

    void on_POMOC_clicked();

    void on_pushButton_4_clicked();


    void on_BTNSYGNAL_2_clicked();

    void on_BTNAMPLITUDA_clicked();

    void on_BTNOKRES_clicked();

    void on_BTNWYPEL_clicked();

    void on_BTNSYGNAL_clicked();

private:
    Ui::MainWindow *ui;
    App* app;
    QChart *chart;           //obiekt wykresu
    QChartView *chartView;   //wykresu
    QLineSeries *seriesY;        //y
    QLineSeries *seriesU;        //u
     QLineSeries *seriesZ;        //zaklucenia
    QValueAxis *axisX;
    QValueAxis *axisY;
    QTimer *timer;           //timer
    int currentX;            //
};
#endif // MAINWINDOW_H
