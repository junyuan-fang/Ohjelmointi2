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
#include <library_operations.hh>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;


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

