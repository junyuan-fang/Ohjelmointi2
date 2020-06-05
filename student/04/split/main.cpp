#include <iostream>
#include <string>
#include <vector>
using namespace std;
// TODO: Implement split function here
// Do not change main function
vector<string> split(string line , char separator, bool ignoring=false){
    char sailio=' ';
    string splited_string="";
    vector<string> return_vector={};

    for(string::size_type i=0; i < line.size(); ++i){
        if (separator==line.at(i)){

            if (ignoring==false){
                return_vector.push_back(splited_string);
                splited_string="";

            }
            else if ((ignoring==true)&&(sailio!=separator)&&(i!=0)){
                return_vector.push_back(splited_string);
                splited_string="";
            }

        }
        else{
            splited_string+=line.at(i);
        }

        if (i==line.size()-1){
            return_vector.push_back(splited_string);
        }
        
        sailio=line.at(i);
    }
    return return_vector;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);

    //line ="---A-B--C--D-E---";

    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
