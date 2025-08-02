#ifndef SPLAYFA_H
#define SPLAYFA_H

#include <iostream>
#include <utility>

using namespace std;

template <typename T>
class SplayFa {
public:
    struct Csomopont {
        T ertek;
        Csomopont* szulo;
        Csomopont* bal;
        Csomopont* jobb;

        Csomopont(const T& ert = T()) : ertek(ert), szulo(nullptr), bal(nullptr), jobb(nullptr) {}
    };

    SplayFa();
    SplayFa(Csomopont* gyoker); // letrehoz egy splay fat a "gyoker" gyokerrel
    ~SplayFa(); // felszabaditja a fanak lefoglalt memoriat

    Csomopont* keres(const T& ertek); // terit egy mutatot az "ertek" erteku csomoponthoz
    void beszur(const T& ertek); // beszurja a faba az "ertek" erteku csomopontot
    void torol(const T& ertek); // kitorli a fabol az "ertek" erteku csomopontot
    void kiir(); // kiirja a fa csomopontjait novekvo sorrendben
    Csomopont* minimum() const; // terit egy mutatot a fa minimum erteku csomopontjahoz
    Csomopont* maximum() const; // terit egy mutatot a fa maximum erteku csomopontjahoz
    Csomopont* elozo(const T& ertek); // terit egy mutatot az "ertek" erteku elem elozojehez
    Csomopont* kovetkezo(const T& ertek); // terit egy mutatot az "ertek" erteku elem kovetkezojehez
    Csomopont* iElem(int i) const; // terit egy mutatot a fa rendezett sorozatbeli i.-ik elemehez
    int rang(const T& ertek); // teriti az "ertek" erteku csomopont rendezett sorozatbeli sorszamat
    void osszeilleszt(SplayFa& masik); // osszeileszti a fat a "masik" faval; a "masik" fa megsemmisul
    pair<Csomopont*, Csomopont*> szetvag(const T& x); // kettevagja a fat az "x" erteku csomopontnal; terit egy-egy mutatot a ket fa gyokereihez

    Csomopont* getGyoker() const;

private:
    Csomopont* gyoker;

    void splay(Csomopont* x); // kiforditja a fat az "x" csomoponttol, "x" a fa gyokere lesz
    void zig(Csomopont* x); // jobb forgatas az "x" csomopontra
    void zag(Csomopont* x); // bal forgatas az "x" csomopontra
    void zigzig(Csomopont* x); // jobb + jobb forgatas az "x" csomopontra
    void zagzag(Csomopont* x); // bal + bal forgatas az "x" csomopontra
    void zigzag(Csomopont* x); // bal + jobb forgatas az "x" csomopontra
    void zagzig(Csomopont* x); // jobb + bal forgatas az "x" csomopontra
};

#include "splayfa.tpp"

#endif //SPLAYFA_H