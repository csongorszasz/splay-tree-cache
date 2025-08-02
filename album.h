#ifndef ALBUM_H
#define ALBUM_H

#include "kep.h"
#include <vector>

using namespace std;

class Album
{
private:
    string nev;
    vector<Kep> kepek;

public:
    Album(const char* nev, const char* utvonal);

    static int osszesKep;

    string getNev() const;
    const vector<Kep>& getKepek() const;
    Kep keres(int id) const;
    void kiir();
};


#endif //ALBUM_H
