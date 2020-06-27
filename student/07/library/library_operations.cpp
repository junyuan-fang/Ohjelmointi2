#include <library_operations.hh>


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
