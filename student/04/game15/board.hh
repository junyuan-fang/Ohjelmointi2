/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 *  Describes a two-dimensional grid for puzzle 15 with necessary functions.
 *
 * Program author ( Fill with your own info )
 * Name: Teemu Teekkari
 * Student number: 292042
 * UserID: fqjufa ( Necessary due to gitlab folder naming. )
 * E-Mail: junyuan.fang@tuni.fi
 *
 * Notes:
 *
 * */

#ifndef BOARD_HH
#define BOARD_HH
#include <vector>
#include <iostream>
using namespace std;

const int SIZE = 4;

class Board
{
public:
    // Constructor
    Board();

    // Initializes the grid randomly based on the seed
    void init(const int& seed);

    // Initialized the grid with the values of numbers vector
    // Returns false, if the given vector does not contain all the numbers [1..16],
    // otherwise returns true
    bool init(const vector<unsigned int>& numbers);

    // Prints the game grid(2D)
    void print() const;

    // Liikkuttaa laattaa, liikkuminen onnistuu silloin, kun kohdepaikalla on tyhjä paikka
    // Print the information to the user, if the moving is not posible
    void move(const string& operation, const unsigned int& luku);

    // check the winning state
    bool is_win() const;

    // Palauttaa ratkaisevuuden totuusarvoa, ja tulostaa ratkaisevuuden tietoa konsolile
    bool is_solvable() const;

private:
    // Shuffles the numbers vector by using seed as a seed value
    void my_shuffle(vector<unsigned int>& numbers, const int& seed);

    //1.Tallentaa yksiulotteinen "Game grid" olion jasenmuuttujaan one_dimesion_grid_
    //2.Muuttaa "Game grid" yksiulotteisesta kaksiulotteiseen,
    //  ja tallennetaan jasenmuuttujaan "grid_".
    void make_grid(const vector<unsigned> &number_list);

    // Luodaan "Game grid"(tallennetaan jasenmuuttujaan win_grid_)
    // myöhemmin kaytettavan pelivoiton("is_win") tarkistusta varten
    void make_win_grid();

    // Funktio paluttaa luku koordinaattistossa(grid_) olevan x- ja y-arvot
    // return : vector{x, y}
    vector<int> return_x_y( unsigned int luku) const ;

    // Game grid for the 15 puzzle, kaksiulotteinen.
    vector<vector<unsigned int>> grid_;

    // Game grid for the 15 puzzle, yksiulotteinen.
    vector<unsigned int> one_dimesion_grid_;

    // Game grid, which shows the  winning permutation
    vector<vector<unsigned int>> win_grid_;


};

#endif // BOARD_HH
