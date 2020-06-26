/* (P)Kirjasto :
 *
 * Desc:
 * Toteuta ohjelma, joka lukee kaynnistyessaan kirjastojen kokoelmiin liittyvia
 * tietoja tiedostosta, tallentaa ne sopivaan tietorakenteeseen ja antaa
 * kayttajalle mahdollisuuden tehda hakuja kyseiseen tietorakenteeseen.
 * Kayttoliittymalla on toteutettu "libraries", "material <kirjasto>",
 * "books <kirjasto> <tekija>", "reservable <kirjan_nimi>", "loanable", "quit"
 * jarjestyksessa
 *
 * Program author ( Fill with your own info )
 * Name: Junyuan Fang
 * Student number: 292042
 * UserID: fajufa ( Necessary due to gitlab folder naming. )
 * E-Mail: junyuan.fang@tuni.fi
 *
 * */
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

// Kutsuu ylla mainitut funktiot
// Tekee kayttoliittyma, josta poistuu kommentolla "quit"
// annetaan virhe ilmoitusta jos komennolle annetaan vaara maara parametreja
int main()
{   string tiedostonimi;
    cout<<"Input file: ";
    getline(cin,tiedostonimi);
    map<string,set<book>>tallennetut_tiedot;
    tiedosdon_lukeminen(tiedostonimi,tallennetut_tiedot);

    while (true){
        string order;
        cout<<"> ";
        getline(cin,order);

        vector<string> order_parts;
        order_parts=split(order,' ',true);

        if(order=="quit"){
            return  EXIT_SUCCESS;
        }

        else if(order_parts.at(0)=="libraries"){
            map<string,set<book>>::iterator iter=tallennetut_tiedot.begin();
            while(iter!=tallennetut_tiedot.end()){
                cout<<iter->first<<endl;
                ++iter;
            }
        }

        else if(order_parts.at(0)=="material"){
            if(order_parts.size()!=2){
                cout<<"Error: error in command "<<order_parts.at(0)<<endl;
            }
            else{
                string kirjasto_nimi=order_parts.at(1);
                materiaali_tulostus(kirjasto_nimi,tallennetut_tiedot);
            }
        }
        //books <kirjasto> <tekija>
        else if(order_parts.at(0)=="books"){
            if (order_parts.size()!=3){
                cout<<"Error: error in command "<<order_parts.at(0)<<endl;
            }
            else{
                string kirjasto_nimi=order_parts.at(1);
                string tekija=order_parts.at(2);
                kirjojen_tulostus(kirjasto_nimi,tekija, tallennetut_tiedot);

            }

        }
        else if (order_parts.at(0)=="reservable"){
            string kirjan_nimi;
            if(order.find("\"")!=string::npos){
                int index_alku = order.find("\"")+1;
                int index_loppu = order.find_last_of("\"");
                kirjan_nimi = order.substr(index_alku,index_loppu-index_alku);
            }
            else{
                vector<string> ::iterator iter=++order_parts.begin();
                while(iter!=order_parts.end()){
                    if(iter!=order_parts.end()-1){
                        kirjan_nimi+=(*iter+" ");
                    }
                    else{
                        kirjan_nimi+=*iter;
                    }
                    ++iter;
                }
            }
            reservable_printing(kirjan_nimi,tallennetut_tiedot);
        }
        else if (order_parts.at(0)=="loanable"){
            lainava_tulostus(tallennetut_tiedot);
        }
        else{
            cout<<"Error: Unknown command: "<<order_parts.at(0)<<endl;
        }
    }
    return EXIT_SUCCESS;
}


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void tiedosdon_lukeminen(const string& tiedostonimi,
                         map<string,set<book>>&tallennetut_tiedot){
    ifstream tiedostomuuttuja(tiedostonimi);
    if(tiedostomuuttuja){
        string rivi;
        int succeed_reading=0;
        while (getline(tiedostomuuttuja,rivi)){
            book kirja;
            vector<string> parts=split(rivi,';',true);
            if (parts.size()!=4){//jos ei ole vaaditussa muodossa
                cout<<"Error: empty field"<<endl;
                exit(1);
            }
            else{
                //tallenetaan luetut tiedot tietuelle
                kirja.author=parts.at(1);
                kirja.title=parts.at(2);
                if(parts.at(3)=="on-the-shelf"){
                    kirja.reservations=0;
                }
                else{
                    kirja.reservations=stoi(parts.at(3));
                }

                string kirjastonimi=parts.at(0);
                //jos kirjaston nimi ei ollut map:ssa
                if(tallennetut_tiedot.find(kirjastonimi)
                        ==tallennetut_tiedot.end()){
                   set<book>books={kirja};
                   tallennetut_tiedot.insert({kirjastonimi,books});
                }
                else{
                    tallennetut_tiedot.at(kirjastonimi).insert(kirja);
                }
            }
            ++succeed_reading;
        }
        if(succeed_reading==0){
            cout<<"Error: empty field"<<endl;
            exit(1);
        }
        tiedostomuuttuja.close();
    }
    else{
        cout<<"Error: the input file cannot be opened"<<endl;
        exit(1);
    }
}
// alkaa nama funktiot, jotka ovat kayttoliittymalle
//ja nama funktiot ovat jarjestyksessa
void materiaali_tulostus(const string& kirjasto_nimi,
                         const collected_data& tallennetut){
    if(tallennetut.find(kirjasto_nimi)==tallennetut.end()){
        cout<<"Error: unknown library name"<<endl;
    }
    else{
        for( book kirja : tallennetut.at(kirjasto_nimi)){
            cout<<kirja.author<<": "<<kirja.title<<endl;
        }
    }
}

void kirjojen_tulostus(const string& kirjasto_nimi,
                       const string& tekija,
                       const collected_data& tallennetut){
    if(tallennetut.find(kirjasto_nimi)==tallennetut.end()){
        cout<<"Error: unknown library name"<<endl;
    }
    else{
        int tekija_loytetty=0;
        set<book> kirjat=tallennetut.at(kirjasto_nimi);
        for( book kirja : kirjat){
            if(kirja.author==tekija){
                if(kirja.reservations==0){
                    cout<<kirja.title<<" --- on the shelf"<<endl;
                }
                else{
                    cout<<kirja.title<<" --- "
                       <<kirja.reservations
                      <<" reservations"<<endl;
                }
                 ++tekija_loytetty;
            }
        }
        if(tekija_loytetty==0){
            cout<<"Error: unknown author"<<endl;
        }
    }
}
// Tulostaa kijan_nimi liittyvan pienimman varausksen luku,
// ja lyhyimman varauksen kirjastojen nimet
void reservable_printing(const string& kirjan_nimi,
                         const collected_data& talletetut){
    vector<string> kirja_vec_struc;
    int min_reservation=0;
    int esiityminen=0;
    for(auto talle: talletetut){//kaydaan map lapi
        string kirjaston_nimi=talle.first;
        set<book>:: iterator iter=talle.second.begin();

        while(iter!=talle.second.end()){//kaydaan set<book> lapi
            int curret_reservation=iter->reservations;

            if(iter->title==kirjan_nimi){
                esiityminen++;
                if(kirja_vec_struc.empty()){
                    kirja_vec_struc.push_back(kirjaston_nimi);
                    min_reservation=curret_reservation;
                }
                else if(!kirja_vec_struc.empty()&&
                        curret_reservation<min_reservation){
                    kirja_vec_struc.erase(kirja_vec_struc.begin(),kirja_vec_struc.end() );
                    kirja_vec_struc.push_back( kirjaston_nimi);
                    min_reservation=curret_reservation;
                }
                else if(!kirja_vec_struc.empty()&&
                        curret_reservation==min_reservation){
                    kirja_vec_struc.push_back( kirjaston_nimi);
                    min_reservation=curret_reservation;
                }
            }
            ++iter;
        }
    }
    if(esiityminen==0){//jos kirja on esiintynyt
        cout<<"Book is not a library book."<<endl;
        return;
    }
    else if (min_reservation>=100){
        cout<<"The book is not reservable from any library."<<endl;
        return;
    }
    else{
        if(min_reservation==0){
            cout<<"on the shelf"<<endl;
        }
        else{
            cout<<min_reservation<<" reservations"<<endl;
        }
        for (string  nimi: kirja_vec_struc){
            cout<<"--- "<<nimi<<endl;
            }
    }

}

void lainava_tulostus(const collected_data& tallennetut_tiedot){
    set<string > tulostettava_set;

    for (auto talle_rivi:tallennetut_tiedot){
        for(book kirja:talle_rivi.second){
            string tulostettava_rivi;
            tulostettava_rivi=kirja.author+": "+kirja.title;
            if(kirja.reservations==0){//jos on the shelf
                tulostettava_set.insert(tulostettava_rivi);//tulostettavn set on tehty
            }
        }
    }

    for (string tulostettava:tulostettava_set){
        cout<<tulostettava<<endl;
    }

}
