#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
using namespace std;

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


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

void print_suhde(map<string,vector<string>>& nimi_lista,
                 string tunniste,
                 int _kerta=0,
                 const char  merkki='.'){

    if(nimi_lista.find(tunniste)==nimi_lista.end()){
        cout<<string(_kerta*2,merkki)<<tunniste<<endl;
    }
    else{
        cout<<string(_kerta*2,merkki)<<tunniste<<endl;
        vector<string> tulostavat_tunnistet=nimi_lista.find(tunniste)->second;
        ++_kerta;
        for(string tunniste: tulostavat_tunnistet){
            print_suhde(nimi_lista,tunniste,_kerta);
            //cout<<string(_kerta*2,merkki)<<tunniste<<endl;
        }
    }
}

unsigned int alihakemisto(const map<string, vector<string>>& nimi_listA, const string& tunniste, int& tulos){
    if(nimi_listA.find(tunniste)==nimi_listA.end()){
        return 0;
    }
    else{
        vector<string> vektori=nimi_listA.find(tunniste)->second;
        for(string tunniste_i : vektori){
            alihakemisto(nimi_listA,tunniste_i,++tulos);
        }
    }
    return tulos;
}

unsigned int depth(const map<string, vector<string>>& nimi_listA,
                   const string& tunniste,
                   int& tulos,
                   int& max){
    if(nimi_listA.find(tunniste)==nimi_listA.end()){
        return 1;
    }

    else{
        vector <string> vektori=nimi_listA.find(tunniste)->second;
        for (string tunniste_i:vektori){
            depth(nimi_listA,tunniste_i,++tulos,max);
            if(max<tulos){
                max=tulos;
                tulos=1;
            }
        }
    }
    return max;
}


int main()
{
    // TODO: Implement the datastructure here
    map<string, vector<string>> nimi_lista;

    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;//hypataan kaikki if-ehto lauseen kaskyt ohi, ja kaikki
                //sama tasoset kaskyt
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            //jos id1 ei ollut, luodaan map:iin
            if(nimi_lista.find(id1)==nimi_lista.end()){
                nimi_lista.insert({id1,{id2}});
            }
            //jos id2 ei ollut id1:ssa, viedaan sisaan vektoriin
            vector<string> kyseinen_vec=nimi_lista.at(id1);
            bool is_in_vec=false;
            for (string tunniste:kyseinen_vec){
                if (tunniste==id2){
                    is_in_vec=true;
                }
            }
            if(!is_in_vec){
                nimi_lista.at(id1).push_back(id2);
            }


        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);
            print_suhde(nimi_lista, id);

            // TODO: Implement the command here!

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);
            int tulos=0;
            cout<<alihakemisto(nimi_lista, id,tulos)<<endl;

            // TODO: Implement the command here!

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);
            int tulos_d=1, max=1;
            cout<<depth(nimi_lista,id, tulos_d,max)<<endl;
            // TODO: Implement the command here!

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
