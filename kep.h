#ifndef KEP_H
#define KEP_H

#include <string>

using namespace std;

struct Kep
{
    int id;
    string cim;

    Kep(){}
    Kep(int id, string cim = "") : id(id), cim(cim){}
};

#include "splayfa.tpp"

#endif //KEP_H
