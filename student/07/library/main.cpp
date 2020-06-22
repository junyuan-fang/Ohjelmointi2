#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <fstream>

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
        else if (n1.title<n2.title){
            return true;
        }
        else{
            return false;
        }
    }
};

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

string tiedosdon_lukeminen(const string& tiedostonimi,map<string,set<book>>&tallennetut_tiedot){
    ifstream tiedostomuuttuja(tiedostonimi);
    if(tiedostomuuttuja){
        string rivi;
        book kirja;
        set<book>books;
        while (getline(tiedostomuuttuja,rivi)){
            vector<string> parts=split(rivi,';');
            if (parts.size()!=4){//jos ei ole vaaditussa muodossa
                cout<<"Error: empty field"<<endl;
                return "FAILED";
            }
            else{
                kirja.author=parts.at(1);
                kirja.title=parts.at(2);
                if(parts.at(3)=="on-the-shelf"){
                    parts.at(3)="1";
                }
                kirja.reservations=stoi(parts.at(3));

                books.insert(kirja);

                //jos kirjaston nimi ei ollut map:ssa
                if(tallennetut_tiedot.find(parts.at(0))==tallennetut_tiedot.end()){
                    tallennetut_tiedot.insert({parts.at(0),books});
                }
                else{
                    tallennetut_tiedot.at(parts.at(0)).insert(kirja);
                }
            }
       }
    }
    else{
        cout<<"Error: the input file cannot be opened"<<endl;
        return "FAILED";
    }
    return "SUCCESS";
}


int main()
{   string tiedostonimi;
    cout<<"Input file: ";
    getline(cin,tiedostonimi);
    map<string,set<book>>tallennetut_tiedot;

    if(tiedosdon_lukeminen(tiedostonimi,tallennetut_tiedot)
            =="FAILED"){
        return EXIT_FAILURE;
    }
    else{//jos onnistuu
        for (auto kirjasto : tallennetut_tiedot){
            cout<<">"<<kirjasto.first<<endl;
            for (auto kirja: kirjasto.second){
                cout<<"------"<<kirja.author<<endl;
                cout<<"------------------"<<kirja.title<<"                "<<kirja.reservations<<endl;
            }
        }
        cout<<tallennetut_tiedot.at("Metso").size()<<endl;
    }

    
    
    return EXIT_SUCCESS;
}
