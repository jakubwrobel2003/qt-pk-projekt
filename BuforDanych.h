#ifndef BUFORDANYCH_H
#define BUFORDANYCH_H
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;

class BuforDanych {
private:
    double zaklucenie;
    int ID;

    vector<double> b;
    vector<double>a;
    double ster;
    double y;
    int i;
    double u;
public:
    static int licznikInstancji; //licznik ile jest danych
    BuforDanych();//konstruktor jak tworzy sie pierwszy to nullptr
    //setery
    void setZaklucenie(double data);
    void setID(int id);
    void setB(const std::string& data);
    void setA(const std::string& data);

    void setU(double data) {
        u = data;
    }
    void setY(double data) {
        y = data;
    }
    void setI(int im){
        i=im;
    }
    //Getter
    double getU() {
        return u;
    }
    double getZaklucenie() const;
    int getID() const;
    int getI()const;
    double getA(int e);
    double getb(int e);
    double getY();
    vector<double> getvectorB() {
        return b;
    }
    vector<double> getvectorA() {
        return b;
    }
    void wypisztabele(); //wypisuje na ekran pojedyncza tablice
    
};
#endif
