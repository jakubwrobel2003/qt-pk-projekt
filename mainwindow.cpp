#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <qlayout.h>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , app(new App())
    , timer(new QTimer(this))


{




    ARX* arx = new ARX();
    Sygnal* syg = new Sygnal();
    PID* pid = new PID(1, 0.1, 0.001);

    app->setSyg(syg);
    app->setARX(arx);
    app->setPID(pid);

    ui->setupUi(this);
    //wykres
    chart = new QChart();


    chart->setBackgroundVisible(true);

    //Y
    seriesY = new QLineSeries();
    seriesY->setName("Y");
    chart->addSeries(seriesY);



    //U
    seriesU = new QLineSeries();
    seriesU->setName("U");
    QPen pen(Qt::yellow);
    pen.setWidth(2);
    seriesU->setPen(pen);
    chart->addSeries(seriesU);
    //zalucenie
    seriesZ = new QLineSeries();
    seriesZ->setName("ZAKLUCENIE");
    QPen pen2(Qt::red);
    pen2.setWidth(2);
    seriesZ->setPen(pen2);
    chart->addSeries(seriesZ);
    //os X
    axisX = new QValueAxis();
    axisX->setRange(1, 100);
    axisX->setTitleText("Czas");
    chart->addAxis(axisX, Qt::AlignBottom);
    seriesY->attachAxis(axisX);
    seriesU->attachAxis(axisX);
    seriesZ->attachAxis(axisX);


    //os y
    axisY = new QValueAxis();
    axisY->setRange(-0.1, 0.1);
    axisY->setTitleText("Wartość");
    chart->addAxis(axisY, Qt::AlignLeft);
    seriesY->attachAxis(axisY);
    seriesU->attachAxis(axisY);
    seriesZ->attachAxis(axisY);
    //tworzenie widoku wykrersu
    chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);

    //dodanie wykresu do widoku cartcontiner
    ui->chartContainer->setLayout(new QVBoxLayout());
    ui->chartContainer->layout()->addWidget(chartView);

    //conect(wysyjacys sygnal,sygnal emitowany pzez,odbiorca,lambda [this]
    //ma dstep do danych w mainwindow
    connect(timer, &QTimer::timeout, this, [this]() {
        app->symulacjaStep();
        updateChart();
    });
}

MainWindow::~MainWindow()
{   delete app;
    delete ui;
}

void MainWindow::on_START_clicked() {
     if (app) {
    app->startSymulacja();
    timer->start(100);      // timer co 100 ms
    qDebug() << "Symulacja uruchomiona.";
    ui->START->setEnabled(false);
    ui->STOP->setEnabled(true);


    ui->ODCZYT->setDisabled(true);
    ui->BTNSETA->setDisabled(true);
    ui->BTNSETB->setDisabled(true);
    ui->BTNKD->setDisabled(true);
    ui->BTNKI->setDisabled(true);
    ui->BTNKP->setDisabled(true);
    ui->RESET->setDisabled(true);
    //ui->SAVE->setDisabled(true);
     }
    else {
         qDebug() << "Błąd: Obiekt `App` nie został zainicjalizowany.";
    }
}

void MainWindow::on_STOP_clicked() {
    if (app) {
    app->stopSymulacja();  // Zatrzymaj symulację
    timer->stop();         // Zatrzymaj timer
    qDebug() << "Symulacja zatrzymana.";
    ui->STOP->setEnabled(false);
    ui->START->setEnabled(true);
    ui->ODCZYT->setDisabled(false);
    ui->BTNSETA->setDisabled(false);
    ui->BTNSETB->setDisabled(false);
    ui->BTNKD->setDisabled(false);
    ui->BTNKI->setDisabled(false);
    ui->BTNKP->setDisabled(false);
    ui->RESET->setDisabled(false);
   // ui->SAVE->setDisabled(false);

    }
    else {
         qDebug() << "Błąd: `app->data` to nullptr";
     }
}

void MainWindow::on_pushButton_clicked()
{
    if (app) { //app?
        app->zapisBazydanychdopliku();


    }
    else {
        qDebug() << "`app->data` to nullptr";
    }
}

void MainWindow::on_ODCZYT_clicked()
{
    if (app) { //app?
        // czyzczenie wykresu
        if (seriesY) {
            seriesY->clear();
        }
        if (seriesU) {
            seriesU->clear();
        }
        if (seriesZ) {
            seriesZ->clear();
        }

        //restart X Y
        if (axisX) {
            axisX->setRange(0, 100);
        }
        if (axisY) {
            axisY->setRange(-0.1, 0.1);
        }
        for (auto& elem : app->data) {
            delete elem; // usun dynamicznie  obiekty
        }
        app->data.clear();

        //
        BuforDanych::licznikInstancji=-1;
        app->odczytajDaneZPliku();

        if (app->data.empty()) {
            qDebug() << "`app->data` to nullptr";
            return;
        }
        for (auto& ostatniElement : app->data) {
            if (ostatniElement) {
                seriesY->append(ostatniElement->getI(), ostatniElement->getY());
                seriesU->append(ostatniElement->getI(), ostatniElement->getU());
                seriesZ->append(ostatniElement->getI(), ostatniElement->getZaklucenie());
                //Rozszerzenie zakresu osi X
                if (ostatniElement->getI() > axisX->max()*0.80) {
                    axisX->setRange(axisX->min() + 1, axisX->max() + 1);
                }
                if (ostatniElement->getY() < axisY->min()*0.8) {
                    axisY->setRange(axisY->min() - 1, axisY->max() );
                }
                if (ostatniElement->getY() > axisY->max()*0.8 ||ostatniElement->getU() > axisY->max()*0.8) {
                    axisY->setRange(axisY->min(), axisY->max()+1 );
                }
                qDebug() << "Zaktualizowano wykres: X =" << ostatniElement->getI()
                         << ", Y =" << ostatniElement->getY()<<",Zaklucenie= "<<ostatniElement->getZaklucenie();
            } else {
                qDebug() <<"`app->data` to nullptr";
            }
        }



        app->wypiszDane();
    }
    else {
        qDebug() << "Błąd: App niezainicjalizwane";
    }
}
void MainWindow::updateChart()
{
    if (app->data.empty()) {
        qDebug() << "Brak danych w `app->data`";
        return;
    }

    BuforDanych* ostatniElement = app->data.back();
    if (ostatniElement) {
        seriesY->append(ostatniElement->getI(), ostatniElement->getY());
        seriesU->append(ostatniElement->getI(), ostatniElement->getU());
        seriesZ->append(ostatniElement->getI(), ostatniElement->getZaklucenie());
        //zwiekszanie wykresy
        if (ostatniElement->getI() > axisX->max()*0.80 ) {
            axisX->setRange(axisX->min() + 1, axisX->max() + 1);
        }
        if (ostatniElement->getY() < axisY->min()*0.8) {
            axisY->setRange(axisY->min() - 1, axisY->max() );
        }
        if (ostatniElement->getY() > axisY->max()*0.8 ||ostatniElement->getU() > axisY->max()*0.8) {
            axisY->setRange(axisY->min(), axisY->max()+1 );
        }
        qDebug() << "Zaktualizowano wykres X =" << ostatniElement->getI()
                 << ", Y =" << ostatniElement->getY()<<",Zaklucenie= "<<ostatniElement->getZaklucenie();
    } else {
        qDebug() << "`app->data` to nullptr";
    }
}

void MainWindow::on_RESET_clicked()
{
    // czyzczenie wykresu
    if (seriesY) {
        seriesY->clear();
    }
    if (seriesU) {
        seriesU->clear();
    }
    if (seriesZ) {
        seriesZ->clear();
    }

    //restart X Y
    if (axisX) {
        axisX->setRange(0, 100);
    }
    if (axisY) {
        axisY->setRange(-0.1, 0.1);
    }

    //czyszczenie bazy
    for (auto& elem : app->data) {
        delete elem; // usun dynamicznie  obiekty
    }
    app->data.clear();

    BuforDanych::licznikInstancji=-1;

}


void MainWindow::on_BTNSETA_clicked()
{
    QString input = ui->INPUTA->toPlainText();
    if (input.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Pole USTAW A nie może być puste!");
        return;
    }
    app->a = input.toStdString();
    // Wyświetl komunikat o sukcesie
    QMessageBox::information(this, "Sukces", "Wartość A została ustawiona jako: " + input);
}


void MainWindow::on_BTNSETB_clicked()
{
    QString input = ui->INPUTB->toPlainText();
    if (input.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Pole USTAW B nie może być puste!");
        return;
    }

    app->b = input.toStdString();
    QMessageBox::information(this, "Sukces", "Wartość B została ustawiona jako: " + input);
}


void MainWindow::on_POMOC_clicked()
{//wzmocnienieProporcjonalne(kp), wzmocnienieCalkujace(ki), wzmocnienieRowniczkujace(kd),
    QString instrukcja = "Instrukcja obsługi aplikacji:\n\n"
                         "1. Wprowadź wartości do pól 'USTAW A' i 'USTAW B' w odpowiednim formacie (np. 0.4;-0.2).\n"
                         "2. Ustaw współczynniki Kp, Ki, Kd za pomocą pól na dole interfejsu.\n"
                         "3. Kliknij przycisk 'START', aby rozpocząć symulację.\n"
                         "4. Użyj przycisku 'RESET', aby zresetować ustawienia. Reset usuwa niezapisane dane\n"
                         "5. Możesz zapisać dane za pomocą przycisku 'ZAPISZ' lub wczytać dane z pliku za pomocą 'ODCZYTAJ Z PLIKU'.\n\n"
                         "Rozwiniecie Skrótów\n\n"
                         "A - Wspolczynik wektora A \n"
                         "A - Wspolczynik wektora B \n"
                         "Kp - Wzmocnienie Proporcjonalne \n"
                         "Ki - Wzmocnienie Calkujace\n"
                         "Kd - Wzmocnienie Rowniczkujace\n";
     QMessageBox::information(this, "POMOC",instrukcja);
}


void MainWindow::on_pushButton_4_clicked()
{
    QString instrukcja1 = "Wybor sygnalu\n\n"
                         "0 - Jednostkowy \n"
                         "1 - Sinusoidalny\n"
                         "2 - Geometryczny\n";
    QMessageBox::information(this, "POMOC",instrukcja1);
}



void MainWindow::on_BTNSYGNAL_2_clicked()
{
    double signalValue = ui->SPINBOXSYGNAL->value();
    app->sygnal=signalValue;
    QMessageBox::information(this, "Sukces", "Wartość sygnału została ustawiona jako: " + QString::number(signalValue));
}



void MainWindow::on_BTNAMPLITUDA_clicked()
{
    double signalValue = ui->SPINBOXAMPLITUDA->value();
    app->syg->setA(signalValue);
    QMessageBox::information(this, "Sukces", "Wartość sygnału została ustawiona jako: " + QString::number(signalValue));
}


void MainWindow::on_BTNOKRES_clicked()
{
    int signalValue = ui->SPINBOXOKRES->value();
    app->syg->sett(signalValue);
    QMessageBox::information(this, "Sukces", "Wartość sygnału została ustawiona jako: "+ QString::number(signalValue) );
    qDebug()<<signalValue;
}


void MainWindow::on_BTNWYPEL_clicked()
{
    double signalValue = ui->SPINBOXWYPELNIENIE->value();
    app->syg->setp(signalValue); // Konwertujemy double na std::string
    QMessageBox::information(this, "Sukces", "Wartość sygnału została ustawiona jako:" + QString::number(signalValue));

}


void MainWindow::on_BTNSYGNAL_clicked()
{
    double signalValue = ui->SPINBOXSYGNAL->value();
    app->sygnal=signalValue;
    QMessageBox::information(this, "Sukces", "Wartość sygnału została ustawiona jako: " + QString::number(signalValue));
}

void MainWindow::on_BTNKP_clicked()
{   qDebug()<<"DUPA";
    double signalValue =ui->SPINBOXKP->value();
    app->Pid->ustawWzmocnienieProporcjonalne(signalValue);
    QMessageBox::information(this, "Sukces", "Wartość sygnału została ustawiona jako: " + QString::number(signalValue));
}


void MainWindow::on_BTNKD_clicked()
{
    double signalValue =ui->SPINBOXKD->value();
    app->Pid->ustawWzmocnienieRowniczkujace(signalValue);
    QMessageBox::information(this, "Sukces", "Wartość sygnału została ustawiona jako: " + QString::number(signalValue));
}

void MainWindow::on_BTNKI_clicked()
{
    double signalValue =ui->SPINBOXKI->value();
    app->Pid->ustawWzmocnienieCalkujace(signalValue);
    QMessageBox::information(this, "Sukces", "Wartość sygnału została ustawiona jako: " + QString::number(signalValue));
}

