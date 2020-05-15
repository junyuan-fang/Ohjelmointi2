/* Game15 (or puzzle 15) : Template code
 *
 * Desc:
 *  This program generates a 15 puzzle. The board is SIZE x SIZE,
 * (original was 4x4) and every round the player chooses a direction and
 * a number tile, making the given tile to be moved to the given direction.
 *  Game will end when the numbers 1-15 (1-16) are in the ascending order,
 * starting from top left and proceeding row by row.
 * Empty space is represented by the number 16 in the code (constant EMPTY)
 * and by dot when printing the game board.
 *
 * Program author ( Fill with your own info )
 * Name: Teemu Teekkari
 * Student number: 123456
 * UserID: teekkart ( Necessary due to gitlab folder naming. )
 * E-Mail: teemu.teekkari@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */

#include "board.hh"
#include <iostream>

bool init_board(Board& g_board)
{
    std::string init_mode = "";
    while(init_mode != "y" and init_mode != "Y" and init_mode != "n" and init_mode != "N")
    {
        std::cout << "Random initialization (y/n): ";
        std::getline(std::cin, init_mode);
        if(init_mode == "y" or init_mode == "Y")
        {
            std::cout << "Enter a seed value (or an empty line): ";
            std::string seed = "";
            std::getline(std::cin, seed);
            if(seed == "")
            {
                g_board.init(time(0));
            }
            else
            {
                g_board.init(stoi(seed));
            }
            return true;
        }
        if(init_mode == "n" or init_mode == "N")
        {
            std::cout << "Enter the numbers 1-16 in a desired order (16 means empty):" << std::endl;
            std::vector<unsigned int> inputs;
            for(unsigned int i = 0; i < SIZE * SIZE; ++i)
            {
                unsigned int input = 0;
                std::cin >> input;
                inputs.push_back(input);
            }
            return g_board.init(inputs);
        }
        std::cout << "Unknown choice: " << init_mode << std::endl;
    }
    return true;  // This should never be reached
}


// More functions

int main()
{
    Board game_board;
    if(!init_board(game_board))
    {
        return EXIT_FAILURE;
    }

    // More functionality

    return EXIT_SUCCESS;
}
