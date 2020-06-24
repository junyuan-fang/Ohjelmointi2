#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <fstream>
#include <string>

//<kirjasto>;<tekija>;<kirjan_nimi>;<varausten_maara>
using namespace std;

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

std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
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

void tiedosdon_lukeminen(const string& tiedostonimi,map<string,set<book>>&tallennetut_tiedot){
    ifstream tiedostomuuttuja(tiedostonimi);
    if(tiedostomuuttuja){
        string rivi;
        int succeed_reading=0;
        while (getline(tiedostomuuttuja,rivi)){
            book kirja;
            vector<string> parts=split(rivi,';');
            if (parts.size()!=4){//jos ei ole vaaditussa muodossa
                cout<<"wrong size"<<endl;
                cout<<"Error: empty field"<<endl;
                exit(1);
            }
            else{
                kirja.author=parts.at(1);
                kirja.title=parts.at(2);
                if(parts.at(3)=="on-the-shelf"){
                    kirja.reservations=1;
                }
                else{
                    kirja.reservations=stoi(parts.at(3));
                }

                string kirjastonimi=parts.at(0);
                //jos kirjaston nimi ei ollut map:ssa
                if(tallennetut_tiedot.find(kirjastonimi)==tallennetut_tiedot.end()){
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
                if(kirja.reservations==1){
                    cout<<kirja.title<<" --- one the shelf"<<endl;
                }
                else{
                    cout<<kirja.title<<" --- "<<kirja.reservations<<" reservations"<<endl;
                }
                 ++tekija_loytetty;
            }
        }
        if(tekija_loytetty==0){
            cout<<"Error: unknown author"<<endl;
        }
    }
}
void reservable_printing(const string& kirjan_nimi, const collected_data& talletetut){
    set<string> kirjastot;
    int reservable=0;
    int esiityminen=0;
    for(auto talle: talletetut){//kaydaan map lapi
        for(book book_struct: talle.second){
            if(book_struct.title==kirjan_nimi){
                reservable+=book_struct.reservations;
                kirjastot.insert(talle.first);
                esiityminen++;
            }           
        }
    }
    cout<<kirjan_nimi<<endl;
    if(esiityminen==0){//jos kirja on esiintynyt
        cout<<"Book is not a library book."<<endl;
        return;
    }
    else if (reservable>=100){
        cout<<"The book is not reservable from any library."<<endl;
        return;
    }
    else{
        cout<<reservable<<" reservations"<<endl;
        for (string nimi: kirjastot){
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
            if(kirja.reservations==1){//jos on the shelf
                tulostettava_set.insert(tulostettava_rivi);//tulostettavn set on tehty
            }
        }
    }

    for (string tulostettava:tulostettava_set){
        cout<<tulostettava<<endl;
    }

}
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
