#ifndef ARX_H
#define ARX_H
#include <random>
#include "App.h"
#include "BuforDanych.h"
using namespace std;
class ARX {
public:
    double generateDisturbance();
    //double policz(std::vector<BuforDanych*> data);
    double calaA(std::vector<BuforDanych*> data);
    double calcb(std::vector<BuforDanych*> data);
    double calcAll(std::vector<BuforDanych*> data);
    // gen zaklucen 0.0 do 1.0
};
//
#endif
