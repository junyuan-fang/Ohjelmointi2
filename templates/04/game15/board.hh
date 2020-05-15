/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 *  Describes a two-dimensional grid for puzzle 15 with necessary functions.
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

#ifndef BOARD_HH
#define BOARD_HH
#include <vector>

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
    bool init(const std::vector<unsigned int>& numbers);

    // Prints the game grid
    void print();

    // More methods

private:
    // Shuffles the numbers vector by using seed as a seed value
    void my_shuffle(std::vector<unsigned int>& numbers, int seed);

    // Game grid for the 15 puzzle
    std::vector<std::vector<unsigned int>> grid_;

    // More attributes/methods
};

#endif // BOARD_HH
