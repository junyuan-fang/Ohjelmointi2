//aman nimisen kilpailijan pisteiden yhteenlaskeminen
//ja kaikkien kilpailijoiden pistemaarien tulostaminen aakkostettuna pelaajan nimen mukaan.
#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;
const char EROTIN=':';

using pisteBoard=map<string, int>;

string get_string(string& input_files){
    cin>>input_files;
    string feed_line;
    getline(cin, feed_line);
    return input_files;
}
void p_tilanteen_muokaus(pisteBoard& pistetilanne,const string& rivi){
    string name;
    int piste;
    int erotimen_indeksi=rivi.find(EROTIN);
    name=rivi.substr(0,erotimen_indeksi);
    piste=stoi(rivi.substr(++erotimen_indeksi));//taalla tarkoittaa indeksi+1
    //jos ei ole pisteBboard:sssa
    if(pistetilanne.find((name))==pistetilanne.end()){
        pistetilanne.insert({name, piste});
    }
    else{
        pistetilanne.at(name)+=piste;
    }
}
void tulostus(const pisteBoard& pistetilanne){
    cout<<"Final scores:"<<endl;
    pisteBoard :: const_iterator iter;
    iter=pistetilanne.begin();
    while (iter!=pistetilanne.end()){
        cout<<iter->first<<": "<<iter->second<<endl;
        ++iter;
    }
}
int main()
{
    string input_files="";
    cout<<"Input file: ";
    input_files=get_string(input_files);

    ifstream tiedostomuutuja(input_files);
    if (!tiedostomuutuja){
        cout<<"Error! The file "<<input_files<<" cannot be opened."<<endl;
        return EXIT_FAILURE;
    }

    else{
        string rivi="";
        pisteBoard  piste_tilanne;
        while(getline(tiedostomuutuja,rivi)){
            p_tilanteen_muokaus(piste_tilanne,rivi);
        }
        tulostus(piste_tilanne);
    }

    return 0;
}

