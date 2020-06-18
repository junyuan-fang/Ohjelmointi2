//sanan esiintymisrivien luku maara ja kaksoispiste ja
//taman jalkeen valilyoneilla ja pilkuilla eroteltuna ne rivinumerot,
//joilla sana esiintyy.
//sana esiintymismaara riviluku

#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void tekee_sanalista(vector<string>& sanalista, const string& rivi){
    string sana;
    for (char charact: rivi){
        if (charact==' '){
            sanalista.push_back(sana);
            sana="";
        }
        else{
            sana+=charact;
        }
    }
    sanalista.push_back(sana);

}

void paivitta_sa_tiedot(map<string, vector<int>>& sanatiedot,const string& sana,const int& rivi_luku){
    if(sanatiedot.find(sana)==sanatiedot.end()){
        sanatiedot.insert({sana,{rivi_luku}});
    }
    else{
        sanatiedot.at(sana).push_back(rivi_luku);
    }
}

void tulostus(const map<string, vector<int>>& sanatiedot){
    map<string, vector<int>>::const_iterator iter=sanatiedot.begin();
    while (iter!=sanatiedot.end()){
        cout<<iter->first<<" "<<iter->second.size()<<": ";
        vector<int>::const_iterator iter_set=iter->second.begin();
        if(iter->second.size()==1){
            cout<<*iter_set<<endl;
        }
        else{
            while(iter_set+1!=iter->second.end()){
                cout<<*iter_set<<", ";
                ++iter_set;
                if(iter_set+1==iter->second.end()){
                    cout<<*iter_set<<endl;
                }
            }
        }
        ++iter;
    }
}
int main()
{
    string file_name;
    cout<<"Input file: ";
    cin>>file_name;

    ifstream tiedostomuuttuja(file_name);
    if(!tiedostomuuttuja){
        cout<<"Error! The file "<<file_name<<" cannot be opened."<<endl;
        return EXIT_FAILURE;
    }
    else{//jos toimii
        string rivi;
        int rivi_luku=1;
        map<string, vector<int>> sanatiedot;//tallennetaan sassa muodossa

        while(getline(tiedostomuuttuja,rivi)){
            vector<string> sanalista;

            tekee_sanalista(sanalista, rivi);
            for (string sana : sanalista){
                paivitta_sa_tiedot(sanatiedot, sana, rivi_luku);
            }

            ++rivi_luku;
        }
        tulostus(sanatiedot);
    }


    return 0;
}
