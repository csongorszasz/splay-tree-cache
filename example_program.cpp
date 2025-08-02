#include <iostream>
#include "splayfa.h"

using namespace std;

int main()
{
    SplayFa<int> sf;
    sf.beszur(4);
    sf.beszur(1);
    sf.beszur(3);
    sf.beszur(6);
    sf.beszur(11);
    sf.kiir();
    cout << endl;
    if (sf.keres(7) != nullptr)
        cout << "-> 7 is in the tree\n";
    else
        cout << "-> 7 is not in the tree\n";

    sf.beszur(7);
    sf.kiir();
    cout << endl;
    if (sf.keres(7) != nullptr)
        cout << "-> 7 is in the tree\n";
    else
        cout << "-> 7 is not in the tree\n";

    cout << "Minimum: " << sf.minimum()->ertek << endl;
    cout << "Maximum: " << sf.maximum()->ertek << endl;

    cout << "7's successor: " << sf.kovetkezo(7)->ertek << endl;
    cout << "7's predecessor: " << sf.elozo(7)->ertek << endl;

    try
    {
        cout << "3rd element: " << sf.iElem(3)->ertek << endl;
    }
    catch (const char *e)
    {
        cerr << "Error: " << e << endl;
        exit(1);
    }
    cout << "7's rank: " << sf.rang(7) << endl;

    cout << "Splitting the tree at 7:" << endl;
    pair<SplayFa<int>::Csomopont *, SplayFa<int>::Csomopont *> ketFa;
    ketFa = sf.szetvag(7);
    SplayFa<int> f1(ketFa.first), f2(ketFa.second);
    cout << "Tree1 -> ";
    f1.kiir();
    cout << endl;
    cout << "Tree2 -> ";
    f2.kiir();
    cout << endl;

    cout << "Joining the two trees:" << endl;
    f1.osszeilleszt(f2);
    cout << "Tree1 -> ";
    f1.kiir();
    cout << endl;
    cout << "Tree2 -> ";
    f2.kiir();
    cout << endl;

    cout << "Deleting 4: " << endl;
    f1.torol(4);
    f1.kiir();
    cout << endl;

    sizeof(SplayFa<int>::Csomopont);
}