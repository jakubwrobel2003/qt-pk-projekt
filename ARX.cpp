#include "ARX.h"
#include "App.h"
#include <QDebug>
using namespace std;

double ARX::generateDisturbance() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-0.001, 0.001);
    return dis(gen);
}

double ARX::calcb(vector<BuforDanych*> data) {
    if (data.empty()) {
        throw std::invalid_argument("Dane s? puste! Nie mozna wykonac obliczen.");
    }
    double sum = 0;
    size_t  m_i = data.back()->getvectorB().size();
    for ( size_t i = 1; i < m_i; i++) {
        if (data.size() < i) {
            sum += 0;
        }
        else {
            // cout << "TEST calcb\n" << data[data.size() - 1 - i]->getU() << data.back()->getb(i) << "\n";
            sum += data[data.size() -1 - i]->getU() * data.back()->getb(i);
            qDebug()<<sum<<"<<b"<<i;
        }
    }
    qDebug()<<sum<<"<<b";
    return sum;
}

double ARX::calaA(vector<BuforDanych*> data) {
    if (data.empty()) {
        throw std::invalid_argument("Dane sa puste! Nie mozna wykona? obliczen.");
    }
    double sum = 0;
    int m_i = data.back()->getvectorA().size();
    // cout << "TEST calca\n" << data.size();
    for (int i = 1; i < m_i; i++) {
        if (data.size() < i) {
            sum += 0;
            qDebug()<<"))))000";
        }
        else {
            //   cout << data[data.size() - 1 - i]->getY() << data.back()->getb(i);
            sum += data[data.size()  -1- i]->getY() * data.back()->getA(i);
            qDebug()<<sum<<"<<a"<<i<< data[data.size()-1- i]->getY()<<"Y"<<data.back()->getA(i)<<"sada"<<data.size()-1-i;
        }
    }
    qDebug()<<sum<<"<<a";
    return sum;
}

double ARX::calcAll(std::vector<BuforDanych*> data) {
    if (data.size() == 1) {
        return 0;
   }
    return calcb(data) - calaA(data) + data.back()->getZaklucenie();
}
