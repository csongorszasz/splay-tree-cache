#ifndef PROJEKT_SPLAYFA_TPP
#define PROJEKT_SPLAYFA_TPP

#include "splayfa.h"

template<typename T>
SplayFa<T>::SplayFa() : gyoker(nullptr){}

template<typename T>
SplayFa<T>::SplayFa(SplayFa::Csomopont* gyoker) : gyoker(gyoker)
{
    if (gyoker != nullptr)
        this->gyoker->szulo = nullptr;
}

template<typename T>
void felszabadit(typename SplayFa<T>::Csomopont* gyoker)
{
    if (gyoker != nullptr)
    {
        felszabadit<T>(gyoker->bal);
        felszabadit<T>(gyoker->jobb);
        delete gyoker;
        gyoker = nullptr;
    }
}

template<typename T>
SplayFa<T>::~SplayFa()
{
    felszabadit<T>(gyoker);
}

template<typename T>
void SplayFa<T>::splay(SplayFa::Csomopont* x)
{
    while (x->szulo != nullptr)
    {
        if (x->szulo->szulo == nullptr)
        {
            if (x == x->szulo->bal)
                zig(x->szulo);
            else
                zag(x->szulo);
        }
        else if (x == x->szulo->bal && x->szulo == x->szulo->szulo->bal)
            zigzig(x);
        else if (x == x->szulo->jobb && x->szulo == x->szulo->szulo->jobb)
            zagzag(x);
        else if (x == x->szulo->jobb && x->szulo == x->szulo->szulo->bal)
            zigzag(x);
        else
            zagzig(x);
    }
}

template<typename T>
void SplayFa<T>::zig(Csomopont* x)
{
    Csomopont* tmp = x->bal;
    x->bal = tmp->jobb;
    if (tmp->jobb != nullptr)
        tmp->jobb->szulo = x;
    tmp->szulo = x->szulo;
    if (x->szulo == nullptr)
        gyoker = tmp;
    else if (x == x->szulo->bal)
        x->szulo->bal = tmp;
    else
        x->szulo->jobb = tmp;
    tmp->jobb = x;
    x->szulo = tmp;
}

template<typename T>
void SplayFa<T>::zag(Csomopont* x)
{
    Csomopont* tmp = x->jobb;
    x->jobb = tmp->bal;
    if (tmp->bal != nullptr)
        tmp->bal->szulo = x;
    tmp->szulo = x->szulo;
    if (x->szulo == nullptr)
        gyoker = tmp;
    else if (x == x->szulo->bal)
        x->szulo->bal = tmp;
    else
        x->szulo->jobb = tmp;
    tmp->bal = x;
    x->szulo = tmp;
}

template<typename T>
void SplayFa<T>::zigzig(SplayFa::Csomopont* x)
{
    zig(x->szulo->szulo);
    zig(x->szulo);
}

template<typename T>
void SplayFa<T>::zagzag(SplayFa::Csomopont* x)
{
    zag(x->szulo->szulo);
    zag(x->szulo);
}

template<typename T>
void SplayFa<T>::zigzag(SplayFa::Csomopont* x)
{
    zag(x->szulo);
    zig(x->szulo);
}

template<typename T>
void SplayFa<T>::zagzig(SplayFa::Csomopont* x)
{
    zig(x->szulo);
    zag(x->szulo);
}

template<typename T>
typename SplayFa<T>::Csomopont* reszfaKeres(typename SplayFa<T>::Csomopont* gyoker, const T& ertek)
{
    if (gyoker == nullptr || ertek == gyoker->ertek)
        return gyoker;
    if (ertek < gyoker->ertek)
        return reszfaKeres<T>(gyoker->bal, ertek);
    return reszfaKeres<T>(gyoker->jobb, ertek);
}

template<typename T>
typename SplayFa<T>::Csomopont* SplayFa<T>::keres(const T& ertek)
{
    SplayFa::Csomopont* kereses = reszfaKeres<T>(gyoker, ertek);
    if (kereses != nullptr)
        splay(kereses);
    return kereses;
}

template<typename T>
typename SplayFa<T>::Csomopont* beszurSeged(typename SplayFa<T>::Csomopont* gyoker, typename SplayFa<T>::Csomopont* szulo, const T& ertek)
{
    if (gyoker == nullptr)
    {
        gyoker = new typename SplayFa<T>::Csomopont(ertek);
        if (szulo != nullptr)
        {
            gyoker->szulo = szulo;
            if (gyoker->ertek < szulo->ertek)
                szulo->bal = gyoker;
            else if (gyoker->ertek > szulo->ertek)
                szulo->jobb = gyoker;
        }
        return gyoker;
    }
    if (ertek < gyoker->ertek)
        return beszurSeged<T>(gyoker->bal, gyoker, ertek);
    if (ertek > gyoker->ertek)
        return beszurSeged<T>(gyoker->jobb, gyoker, ertek);
    return gyoker;
}

template<typename T>
void SplayFa<T>::beszur(const T& ertek)
{
    Csomopont* beszurt = beszurSeged<T>(gyoker, nullptr, ertek);
    if (gyoker == nullptr)
        gyoker = beszurt;
    splay(beszurt);
}

template<typename T>
void SplayFa<T>::torol(const T& ertek)
{
    if (gyoker == nullptr)
        return;
    pair<Csomopont*, Csomopont*> fak = szetvag(ertek);
    gyoker = fak.first;
    SplayFa<T> tmp(fak.second);
    osszeilleszt(tmp);
}

template<typename T>
void inorder(typename SplayFa<T>::Csomopont* gyoker)
{
    if (gyoker == nullptr)
        return;
    inorder<T>(gyoker->bal);
    cout << gyoker->ertek << " ";
    inorder<T>(gyoker->jobb);
}

template<typename T>
void SplayFa<T>::kiir()
{
    if (gyoker != nullptr)
        inorder<T>(gyoker);
}

template<typename T>
typename SplayFa<T>::Csomopont* reszfaMinimum(typename SplayFa<T>::Csomopont* gyoker)
{
    if (gyoker->bal != nullptr)
        return reszfaMinimum<T>(gyoker->bal);
    return gyoker;
}

template<typename T>
typename SplayFa<T>::Csomopont* SplayFa<T>::minimum() const
{
    if (gyoker == nullptr)
        return nullptr;
    return reszfaMinimum<T>(gyoker);
}

template<typename T>
typename SplayFa<T>::Csomopont* reszfaMaximum(typename SplayFa<T>::Csomopont* gyoker)
{
    if (gyoker->jobb != nullptr)
        return reszfaMaximum<T>(gyoker->jobb);
    return gyoker;
}

template<typename T>
typename SplayFa<T>::Csomopont* SplayFa<T>::maximum() const
{
    if (gyoker == nullptr)
        return nullptr;
    return reszfaMaximum<T>(gyoker);
}

template<typename T>
typename SplayFa<T>::Csomopont* elsoKisebbElod(typename SplayFa<T>::Csomopont* gyoker)
{
    if (gyoker->szulo == nullptr)
        return nullptr;
    if (gyoker->szulo->bal == gyoker)
        return elsoKisebbElod<T>(gyoker->szulo);
    return gyoker->szulo;
}

template<typename T>
typename SplayFa<T>::Csomopont* SplayFa<T>::elozo(const T& ertek)
{
    Csomopont* akt = keres(ertek);
    if (akt == nullptr)
        return nullptr;
    if (akt->bal != nullptr)
        return reszfaMaximum<T>(akt->bal);
    return elsoKisebbElod<T>(akt);
}

template<typename T>
typename SplayFa<T>::Csomopont* elsoNagyobbElod(typename SplayFa<T>::Csomopont* gyoker)
{
    if (gyoker->szulo == nullptr)
        return nullptr;
    if (gyoker->szulo->jobb == gyoker)
        return elsoNagyobbElod<T>(gyoker->szulo);
    return gyoker->szulo;
}

template<typename T>
typename SplayFa<T>::Csomopont* SplayFa<T>::kovetkezo(const T& ertek)
{
    Csomopont* akt = keres(ertek);
    if (akt == nullptr)
        return nullptr;
    if (akt->jobb != nullptr)
        return reszfaMinimum<T>(akt->jobb);
    return elsoNagyobbElod<T>(akt);
}

template<typename T>
typename SplayFa<T>::Csomopont* inorder(typename SplayFa<T>::Csomopont* gyoker, int& aktSorszam, int i)
{
    typename SplayFa<T>::Csomopont* bal = nullptr;
    typename SplayFa<T>::Csomopont* jobb = nullptr;

    if (gyoker->bal != nullptr)
        bal = inorder<T>(gyoker->bal, aktSorszam, i);

    aktSorszam++;
    if (aktSorszam == i)
        return gyoker;

    if (gyoker->jobb != nullptr)
        jobb = inorder<T>(gyoker->jobb, aktSorszam, i);

    return bal != nullptr ? bal : jobb;
}

template<typename T>
typename SplayFa<T>::Csomopont* SplayFa<T>::iElem(int i) const
{
    int aktSorszam = 0;
    Csomopont* er = inorder<T>(gyoker, aktSorszam, i);
    if (aktSorszam < i)
        throw("Index kiment a hatarokbol");
    return er;
}

template<typename T>
int inorderRang(typename SplayFa<T>::Csomopont* gyoker, int& aktSorszam, const T& ertek)
{
    int bal = -1, jobb = -1;

    if (gyoker->bal != nullptr)
        bal = inorderRang<T>(gyoker->bal, aktSorszam, ertek);

    aktSorszam++;
    if (gyoker->ertek == ertek)
        return aktSorszam;

    if (gyoker->jobb != nullptr)
        jobb = inorderRang<T>(gyoker->jobb, aktSorszam, ertek);

    return bal != -1 ? bal : jobb;
}

template<typename T>
int SplayFa<T>::rang(const T& ertek)
{
    typename SplayFa<T>::Csomopont* akt = keres(ertek);
    if (akt == nullptr)
        return -1;
    int aktSorszam = 0;
    return inorderRang<T>(gyoker, aktSorszam, ertek);
}

template<typename T>
void SplayFa<T>::osszeilleszt(SplayFa& masik)
{
    if (gyoker == nullptr)
    {
        gyoker = masik.gyoker;
        masik.gyoker = nullptr;
        return;
    }
    if (masik.gyoker == nullptr)
        return;

    if (maximum()->ertek > masik.minimum()->ertek)
    {
        throw("Nem lehet osszeilleszteni a ket fat");
    }

    splay(maximum());
    gyoker->jobb = masik.gyoker;
    masik.gyoker->szulo = gyoker;
    masik.gyoker = nullptr;
}

template<typename T>
pair<typename SplayFa<T>::Csomopont*, typename SplayFa<T>::Csomopont*> SplayFa<T>::szetvag(const T& x)
{
    Csomopont* csp = keres(x);
    if (csp == nullptr)
    {
        throw("Nem lehet szetvagni a fat");
    }
    Csomopont *f1 = nullptr, *f2 = nullptr;
    if (gyoker->jobb != nullptr)
    {
        f2 = gyoker->jobb;
        f2->szulo = nullptr;
        gyoker->jobb = nullptr;
    }
    if (gyoker->bal != nullptr)
    {
        f1 = gyoker->bal;
        f1->szulo = nullptr;
    }
    delete gyoker;
    gyoker = nullptr;
    return make_pair(f1, f2);
}

template<typename T>
typename SplayFa<T>::Csomopont* SplayFa<T>::getGyoker() const
{
    return gyoker;
}

#endif //PROJEKT_SPLAYFA_TPP
