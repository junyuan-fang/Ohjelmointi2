/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 *
 * Program author ( Fill with your own info )
 * Name: Teemu Teekkari
 * Student number: 123456
 * UserID: teekkart ( Necessary due to gitlab folder naming. )
 * E-Mail: teemu.teekkari@tuni.fi
 *
 * Notes:
 *
 * */

#include "board.hh"
#include <iostream>
#include <iomanip>
#include <random>
using namespace std;

const int EMPTY = 16;
const unsigned int PRINT_WIDTH = 5;
const int RIVI=4;
const int SARAKE=RIVI;

Board::Board()
{
    // Add code when necessary
}

void Board::make_grid(const vector<unsigned int > &number_list){
//conver vector<unsigned> to vector<vector<unsigned>>
    vector<vector <unsigned int >> grid;
    int indeksi=0;
    for (int rivi=0;rivi<RIVI;++rivi){
        vector <unsigned int > rivi_vector;
        for (int sarake=0;sarake<SARAKE;++sarake){
            rivi_vector.push_back(number_list.at(indeksi));
            indeksi++;
        }
        grid.push_back(rivi_vector);
    }
    grid_=grid;
}
void Board::init(const int seed)
//alustus, tässä käytetään <random> eli 1-15 ovat satunnaisessa järjestyksessä.
{
    vector<unsigned> numbers(16,0);

    for (int i =0; i< 16; ++i){
        numbers.at(i)=i+1;
    }
    my_shuffle(numbers,seed);
    make_grid(numbers);
}


bool Board::init(const vector<unsigned int> &numbers)
//alustus, ohjelman käyttäjä itse antaman 1-15 luvuiden järjestyksen avulla
{
    make_grid(numbers);
    return true;
}

void Board::print() const
{
    for(unsigned int x = 0; x < SIZE; ++x)
    {
        cout << string(PRINT_WIDTH * SIZE + 1, '-') << endl;
        for(unsigned int y = 0; y < SIZE; ++y)
        {
            cout << "|" << setw(PRINT_WIDTH - 1);
            if(grid_.at(x).at(y) != EMPTY)
            {
                cout << grid_.at(x).at(y);
            }
            else
            {
                cout << ".";
            }
        }
        cout << "|" << endl;
    }
    cout << string(PRINT_WIDTH * SIZE + 1, '-') << endl;
}

void Board::my_shuffle(vector<unsigned int> &numbers, int seed)
{
    default_random_engine randomEng(seed);
    uniform_int_distribution<int> distr(0, numbers.size() - 1);
    for(unsigned int i = 0; i < numbers.size(); ++i)
    {
        unsigned int random_index = distr(randomEng);
        unsigned int temp = numbers.at(i);
        numbers.at(i) = numbers.at(random_index);
        numbers.at(random_index) = temp;
    }
}

