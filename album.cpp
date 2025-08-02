#include "album.h"
#include <fstream>
#include <iostream>

using namespace std;

int Album::osszesKep = 0;

Album::Album(const char* albumnev, const char* utvonal) : nev(albumnev)
{
    ifstream fin(utvonal);
    while (!fin.eof())
    {
        string sor;
        getline(fin, sor);
        kepek.push_back(Kep(osszesKep++, sor));
    }
}

string Album::getNev() const
{
    return nev;
}

const vector<Kep>& Album::getKepek() const
{
    return kepek;
}

Kep Album::keres(int id) const
{
    for (Kep kep : kepek)
        if (kep.id == id)
            return kep;
    return Kep();
}

void Album::kiir()
{
    int dbKiirt = 0;
    int szelesseg = 15;
    for (auto kep : kepek)
    {
        dbKiirt++;
        cout << kep.id << "\t";
        if (dbKiirt % szelesseg == 0)
            cout << "\n";
    }
    if (dbKiirt % szelesseg != 0)
        cout << "\n";
}