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

Board::Board()
{
    make_win_grid();
    // Add code when necessary
}

bool Board::is_solvable(){
    int inversio=0;
    for(unsigned int i=2; i<16; i++){

        for (int y=0;y<SIZE;++y){
            for(int x=0; x<SIZE; ++x){
                //estitaan inversioita
                unsigned int luku_inversio_vert=grid_.at(y).at(x);
                if(luku_inversio_vert==i){
                    for (int yy=y; yy<SIZE;++yy){
                        for (int xx=x; xx<SIZE;++xx){
                            if ( grid_.at(yy).at(xx)<luku_inversio_vert){
                                inversio++;
                            }
                        }
                    }
                }
            }
        }

    }
    if (inversio%2==0){
        cout<<"Game is solvable: Go ahead!"<<endl;
        return true;
    }
    else{
        return false;
    }
}

void Board::make_grid(const vector<unsigned int > &number_list){
//conver vector<unsigned> to vector<vector<unsigned>>
    vector<vector <unsigned int >> grid;
    int indeksi=0;
    for (int rivi=0;rivi<SIZE;++rivi){
        vector <unsigned int > rivi_vector;
        for (int sarake=0;sarake<SIZE;++sarake){
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
//alustaa ohjelman käyttäjä antaman 1-16 luvuiden järjestyksella
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

vector< int> Board::return_x_y( unsigned int luku) {
    for ( int y=0; y<SIZE;++y){
        for ( int x =0 ; x<SIZE; ++x){
            if (grid_.at(y).at(x)==luku){
                return {y,x};
            }
        }
    }
    return {EMPTY};//
}

void Board :: move(const char& operation, unsigned int luku){
    //sarake indeksi= y , rivi indeksi=x

    int y= return_x_y(luku).at(0);
    int x= return_x_y(luku).at(1);

    int x_alussa=x;
    int y_alussa=y;
    int temp_nu=grid_.at(y_alussa).at(x_alussa);

    if (operation=='a'){
        --x;
    }
    else if (operation=='d'){
        ++x;
    }
    else if (operation=='w'){
        --y;
    }
    else if (operation=='s'){
        ++y;
    }

    //luvun vaihtaminen
    //vaihtaminen tapahtuu ainoastaan silloin, kun vastaavalla indeksilla on tyhja paikka
    if ((y<0)or(x<0)or grid_.at(y).at(x)!=16){
        cout<<"Impossible direction: "<<operation<<endl;
    }
    else{
        grid_.at(y_alussa).at(x_alussa)=grid_.at(y).at(x);
        grid_.at(y).at(x)= temp_nu;
    }
}

void Board::make_win_grid(){
    vector<vector <unsigned int >> win_grid;
    unsigned int value=0;
    for (int rivi=0;rivi<SIZE;++rivi){
        vector <unsigned int > rivi_vector;
        for (int sarake=0;sarake<SIZE;++sarake){
            ++value;
            rivi_vector.push_back(value);
        }
        win_grid.push_back(rivi_vector);
    }
    win_grid_=win_grid;
}
bool Board::is_win(){
    int right_times=0;
    for ( int y=0; y<SIZE;++y){
        for ( int x =0 ; x<SIZE; ++x){
            if (grid_.at(y).at(x)==win_grid_.at(y).at(x)){
                ++right_times;

            }
        }
    }
    if(right_times==16){
        return true;
    }
    else{
        return false;
    }
}
