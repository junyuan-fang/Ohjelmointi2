#ifndef LIBRARY_OPERATIONS_HH
#define LIBRARY_OPERATIONS_HH

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;

//Tietue, joka on set:lla ja map:lla aakkosjarjestyksessa
struct book {
    string title;
    string author;
    int reservations;
    friend bool operator<(const book& n1, const book& n2){
        if(n1.author<n2.author){
            return true;
        }
        else if(n1.author==n2.author){
            return n1.title<n2.title;
        }
        else{
            return false;
        }
    }
};


using collected_data=map<string,set<book>>;

// Lukee rivi, jakaa rivi erotimella. Parametrilla pystyy paatella,
// etta ohitetaanko tyhjaa merkkia vai ei
// return: vector<string>:: palauttaa jaetun rivi vektorilla
std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty );

// map<string,set<book>> tietorakenteen alustus, lukee
// <kirjasto>;<tekija>;<kirjan_nimi>;<varausten_maara> muodossa olevan tiedostoa,
// ja tallennetaan tietoa  map<string,set<book>> muotoon.
// Ohjelma paattyy ja funktio palauttaa EXIT_FAILURE,
// kun tiedoston avaamisesta esiintyy ongelmia, tai, tiedosto on tyhja,
// tai luetun rivi ei ole <kirjasto>;<tekija>;<kirjan_nimi>;<varausten_maara> muodossa
void tiedosdon_lukeminen(const string& tiedostonimi,
                         map<string,set<book>>&tallennetut_tiedot);

// Kaydaan map<string,set<book>> muodossa tallennetut tiedot lapi
// Tulostaa aakkosjarjestyksessa allekkain kaikki annetun kirjaston kirjat
// author+title
// annetaan virheilmoitusta, jos kirjanimi ei loydy keraatylla datalla
void materiaali_tulostus(const string& kirjasto_nimi,
                         const collected_data& tallennetut);

// tulostaa kirjan nimen mukaisessa aakkosjarjestyksessa kaikki
// kyseisen tekijan kirjat, jotka loytyvat kyseisesta kirjastosta,
// seka kirjojen varaustiedot.
// annetaan virheilmoitusra, jos author tai library name ei loydeta
void kirjojen_tulostus(const string& kirjasto_nimi,
                       const string& tekija,
                       const collected_data& tallennetut);

// tulostaa lyhyimman varausjonon halutulle kirjalle ja sen alle
// aakkosjarjestyksessa kirjastot, joista kirja loytyy talla samanpituisella
// varausjonolla.
// annetaan virheilmoitusta, jos kirja on tuntematon, tai sen varausjono
// on liian pitka.
void reservable_printing(const string& kirjan_nimi,
                         const collected_data& talletetut);

// tulostaa naytole kaikkien kirjastojen kaikista kirjoista ne, jotka loytyvat
// hyllysta. Kirjoista tulostetaan tekija ja nimi. Tulostettavassa listassa kirjan
// tekijat ovat aakkosjarjestyksessa ja jokainen kirja on listalla vain kerran.
void lainava_tulostus(const collected_data& tallennetut_tiedot);

#endif // LIBRARY_OPERATIONS_HH
