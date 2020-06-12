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
    void init(int seed);

    // Initialized the grid with the values of numbers vector
    // Returns false, if the given vector does not contain all the numbers [1..16],
    // otherwise returns true
    bool init(const vector<unsigned int>& numbers);

    // Prints the game grid
    void print() const;

    void move(const char& operation, unsigned int luku);

    //check the winning state
    bool is_win();

    bool is_solvable();

private:
    // Shuffles the numbers vector by using seed as a seed value
    void my_shuffle(vector<unsigned int>& numbers, int seed);

    //change vector<unsigned> to vector<vector<unsigned>>
    void make_grid(const vector<unsigned> &number_list);

    void make_win_grid();

    // Game grid for the 15 puzzle
    vector<vector<unsigned int>> grid_;

    // Game grid, which permutation means player wins
    vector<vector<unsigned int>> win_grid_;

    vector<int> return_x_y( unsigned int luku) ;
    // More attributes/methods
};

#endif // BOARD_HH
