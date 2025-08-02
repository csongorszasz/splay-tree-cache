#include "album.h"
#include "splayfa.h"

#include <iostream>
#include <vector>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define ERVENYTELEN -1
#define VISSZALEP -2

// szukseges megadni, hogy mikor kisebb egy "Kep" egy masiknal
bool operator<(const Kep &a, const Kep &b)
{
    return a.id < b.id;
}

// szukseges megadni, hogy mikor nagyobb egy "Kep" egy masiknal
bool operator>(const Kep &a, const Kep &b)
{
    return a.id > b.id;
}

// szukseges megadni, hogy mikor egyenlo egy "Kep" egy masikkal
bool operator==(const Kep &a, const Kep &b)
{
    return a.id == b.id;
}

void beolvas(const char *katalogus, vector<Album> &albumok)
{
    struct stat sb;
    for (const auto &entry : filesystem::directory_iterator(katalogus))
    {
        filesystem::path outfilename = entry.path();
        string outfilename_str = outfilename.string();
        const char *path = outfilename_str.c_str();

        if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR))
        {
            // az utvonalbol kivagjuk az allomany nevet; az kezdobetut nagybetuve alakitjuk -> ez lesz az album neve
            string albumnev = filesystem::path(path).stem().string();
            albumnev[0] = toupper(albumnev[0]);

            albumok.push_back(Album(albumnev.c_str(), path));
        }
    }
}

bool ervenyesBemenet(string bemenet, int albumokSzama)
{
    for (int i = 0; i < bemenet.length(); i++)
        if (!isdigit(bemenet[i]))
            return false;
    int beInt = atoi(bemenet.c_str());
    return beInt >= 1 && beInt <= albumokSzama;
}

bool ervenyesBemenet(string bemenet, Album &album)
{
    if (bemenet == "")
        return false;
    for (int i = 0; i < bemenet.length(); i++)
        if (!isdigit(bemenet[i]))
            return false;
    int beInt = atoi(bemenet.c_str());
    for (auto kep : album.getKepek())
    {
        if (kep.id == beInt)
            return true;
    }
    return false;
}

int lekerAlbumszam(int albumokSzama)
{
    cout << "\nWhich album would you like to view?\n";
    string valasz;
    getline(cin, valasz);
    if (!ervenyesBemenet(valasz, albumokSzama))
    {
        cout << "Invalid input: Please enter a number between 1 and " << albumokSzama << "!\n";
        return ERVENYTELEN;
    }
    return atoi(valasz.c_str());
}

int lekerKepszam(Album &album)
{
    cout << "\nWhich image would you like to view?\n";
    string valasz;
    getline(cin, valasz);
    if (valasz == "..")
        return VISSZALEP;
    if (!ervenyesBemenet(valasz, album))
    {
        cout << "Invalid input: The specified image is not in this catalog!\n";
        return ERVENYTELEN;
    }
    return atoi(valasz.c_str());
}

void kiirOpciok(vector<Album> &albumok)
{
    system("clear");
    string fejlec = "--- Albums ---";
    cout << fejlec << "\n";

    for (int i = 0; i < albumok.size(); i++)
    {
        cout << i + 1 << ".\t" << albumok[i].getNev() << endl;
    }
}

void kiirOpciok(Album &album)
{
    system("clear");
    string fejlec = "--- Albums/";
    fejlec.append(album.getNev());
    fejlec.append(" ---");
    cout << fejlec << "\n";

    cout << ".. (back)\n";
    album.kiir();
}

void megjelenitKep(Kep &kep)
{
    system("clear");
    cout << kep.cim << "\n\n";
}

int main()
{
    // albumok beolvasasa
    vector<Album> albumok;
    beolvas("data", albumok);

    SplayFa<Kep> splayfa;

    int menuSzint = 1;
    int albumszam;
    int kepszam;
    while (true)
    {
        // album kivalasztasa
        if (menuSzint == 1)
        {
            kiirOpciok(albumok);
            albumszam = lekerAlbumszam(albumok.size());

            if (albumszam == ERVENYTELEN)
                sleep(2);
            else
            {
                albumszam--; // a felhasznalotol kert bemenet szerint az albumok 1-tol vannak indexelve, de az "albumok" tomb 0-tol indexelt
                menuSzint = 2;
            }
        }

        // kep kivalasztasa
        else if (menuSzint == 2)
        {
            kiirOpciok(albumok[albumszam]);
            kepszam = lekerKepszam(albumok[albumszam]);
            if (kepszam == ERVENYTELEN)
                sleep(2);
            else if (kepszam == VISSZALEP)
                menuSzint = 1;
            else
                menuSzint = 3;
        }

        // kep megjelenitese
        else if (menuSzint == 3)
        {
            Kep keresettKep;

            // inditunk egy orat, hogy lemerjuk a kereses altal igenyelt idot
            auto idoStart = high_resolution_clock ::now();

            // megprobaljuk megkeresni a kepet a splay faban:
            auto kereses = splayfa.keres(kepszam);

            // ha nem talaltuk meg a faban, akkor megkeressuk a megfelelo albumban es beszurjuk a faba
            if (kereses == nullptr)
            {
                keresettKep = albumok[albumszam].keres(kepszam);
                splayfa.beszur(keresettKep);
            }
            else
                keresettKep = kereses->ertek;

            // leallitjuk az orat es meghatarozzuk az eltelt ido merteket
            auto idoStop = high_resolution_clock ::now();
            duration<double> idotartam = idoStop - idoStart;

            // megjelenitjuk a kepet
            megjelenitKep(keresettKep);

            // kiirjuk a keresesi idot
            cout << "search time: " << fixed << idotartam.count() << "s" << endl;

            // szuneteltetjuk a program futasat, amig a felhasznalo le nem nyom egy billentyut
            cout << "Press Enter to continue...";
            cin.get();

            menuSzint = 2;
        }
    }
}