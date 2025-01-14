#include "App.h"
#include <iostream>
#include <QDebug>
using namespace std;

App::App()
    : run(false),
    data(0),
    arx(nullptr) {
    a="0.2;0.05";
    b="0.7;-0.1";
    sygnal=0;
};
//nowaBaza->setB("0.4;-0.2");
//nowaBaza->setA("0.3;0,1");
App::~App() {
 
}

//void App::clikrun() {
//    run = !run;
//}

void App::startSymulacja() {
    std::cout << "Symulacja rozpoczêta.\n";
    run = true;
}

void App::stopSymulacja() {
    run = false;
    std::cout << "zatrzymana.\n";
}
void App::symulacjaStep() {
    if (!run) {
        return;  //zatrzymana
    }

    BuforDanych* nowaBaza = new BuforDanych();

    nowaBaza->setB(b);
    nowaBaza->setA(a);
    nowaBaza->setZaklucenie(arx->generateDisturbance());


    /*if (data.empty()) {
        nowaBaza->setU(Pid->obliczSprzezenie(0.5, 0));
    } else {
        BuforDanych* ostatni = data.back();
        double poprzednieY = ostatni->getY();
        nowaBaza->setU(Pid->obliczSprzezenie(1, poprzednieY));
    }*/
    syg->seti(nowaBaza->getID());
    qDebug()<<syg->generateSignal(sygnal);
    if (data.empty()) {
        nowaBaza->setU(Pid->obliczSprzezenie(syg->generateSignal(sygnal), 0));
        //

    } else {
        BuforDanych* ostatni = data.back();
        double poprzednieY = ostatni->getY();
        nowaBaza->setU(Pid->obliczSprzezenie(syg->generateSignal(sygnal), poprzednieY));


    }

    data.push_back(nowaBaza);

   if (arx) {
        double wynikCalcAll = arx->calcAll(data);
        data.back()->setY(wynikCalcAll);
    }

    // Debug: Informacje o dodanych danych
    qDebug() << "Dodano punkt do symulacji: ID =" << data.back()->getI()
             << ", Y =" << data.back()->getY();
}


void App::symulacja(bool start) {
    run = start; // Ustawia flagê run
    if (start) {
        std::cout << "Symulacja rozpoczêta.\n";
    } else {
        std::cout << "Symulacja zatrzymana.\n";
    }
}



void App::wypiszDane() {

    std::cout << "Rozmiar danych: " << data.size() << "\n";
    std::cout << "ID\tZaklucenie\tB\tA\tY\tU\n";
    std::cout << "------------------------\n";

    for (const auto& elem : data) {
        if (elem) {
            elem->wypisztabele();
        }
        else {
            std::cout << "B³¹d: pusty wskaŸnik w danych.\n";
        }
    }
}

void App::zapisBazydanychdopliku() {


    ofstream file("example.txt");
    if (file.is_open()) {
        for (const auto& elem : data) {
          
            if (elem) {
                file << elem->getID() << "\t" << elem->getZaklucenie() << "\t";
               
               for (const auto data : elem->getvectorB()) {
                   file << data << ";";
                }
                file << "\t";
               for (const auto data : elem->getvectorA()) {
                  file << data << ";";
               }
                file << "\t";
                file << elem->getY() << "\t" << elem->getU() << "\t";
                file<< Pid->getWzmocnienieCalkujace()<<"\t"<<Pid->getWzmocnienieProporcjonalne()<<"\t"<<Pid->getWzmocnienieRowniczkujace()<< "\n";
                qDebug()<< Pid->getWzmocnienieCalkujace()<<"\t"<<Pid->getWzmocnienieProporcjonalne()<<"\t"<<Pid->getWzmocnienieRowniczkujace()<< "\n";
            }
            else {
                std::cout << "B³¹d: pusty wskaŸnik w danych.\n";
            }
        }
    }
    file.close();
}
