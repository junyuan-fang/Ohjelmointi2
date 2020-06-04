#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.at(i)=new_integer;
        // TODO: Implement your solution here
    }
}

// TODO: Implement your solution here
bool same_values(const vector<int>&ints_vec){
    int i=0;
    int sailio;

    for (int alkio: ints_vec){
        if (i!=0){
            if (alkio!=sailio){
                return false;
            }
        }
        sailio=alkio;
        ++i;
    }
    return true;
}

bool is_ordered_non_strict_ascending(const vector<int>&vector_int){
    int sailio;
    for(std::vector<int>::size_type i=0; i<vector_int.size();++i){
        if (i!=0){
            if (sailio<vector_int.at(i)){
                return false;
            }
        }
        sailio=vector_int.at(i);
    }
    return true;
}

bool is_arithmetic_series(vector<int>&integers){
    int sailio;
    int vakio;
    for (std::vector<int>::size_type i =0; i<integers.size(); ++i ){
        if (i==1){
            vakio=integers.at(i)-sailio;
        }else if (i>1){
            if ((integers.at(i)-sailio)!=vakio){
                return false;
            }
        }
        sailio=integers.at(i);
    }
    return true;
}


bool is_geometric_series(std::vector<int> &integers){
    int i =0;
    int sailio=0;
    double vakio;
    for (int alkiot :integers){
        if(i==1){
            vakio=alkiot/sailio;
        }
        else if ((i>1)&&(alkiot/sailio!=vakio)){
            return false;
        }
        sailio=integers.at(i);
        ++i;
    }
    return true;
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
