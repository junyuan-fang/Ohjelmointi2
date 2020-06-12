/* Game15 (or puzzle 15) : Template code
 *
 * Desc:
 *  This program generates a 15 puzzle. The board is SIZE x SIZE,
 * (original was 4x4) and every round the player chooses a direction and
 * a number tile, making the given tile to be moved to the given direction.
 *  Game will end when the numbers 1-15 (1-16) are in the c order,
 * starting from top left and proceeding row by row.
 * Empty space is represented by the number 16 in the code (constant EMPTY)
 * and by dot when printing the game board.
 *
 * Program author ( Fill with your own info )
 * Name: Junyuan Fang
 * Student number: 292042
 * UserID: fajufa ( Necessary due to gitlab folder naming. )
 * E-Mail: junyuan.fang@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */

#include "board.hh"
#include <iostream>
using namespace std;

//antaa "random initialization" vaihtoehtot, joko .init avulla väittää seed value tai 
//.init metodilla väittää vektori, jolla on arvot 1-15 jäejestyksessä
bool is_misssing_num(vector<unsigned int>& number){
    vector<unsigned int> for_checkl;
    for(unsigned int i=1; i<17;++i){
        for_checkl.push_back(i);
    }


    for(int i=0; i<16; ++i){
        int not_fount=0;
        for(int w=0; w<16;++w){
            if (for_checkl.at(i)!=number.at(w)){
                ++not_fount;
            }
            if (not_fount==16){
                cout<<"Number "<<for_checkl.at(i)<<" is missing"<<endl;
                return true;
            }
        }
    }
    return false;
}
bool init_board(Board& g_board)
{
    string init_mode = "";
    while(init_mode != "y" and init_mode != "Y" and init_mode != "n" and init_mode != "N")
    {
        cout << "Random initialization (y/n): ";
        getline(cin, init_mode);
        if(init_mode == "y" or init_mode == "Y")
        {
            cout << "Enter a seed value (or an empty line): ";
            string seed = "";
            getline(cin, seed);
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
            cout << "Enter the numbers 1-16 in a desired order (16 means empty):" << std::endl;
            vector<unsigned int> inputs;
            for(unsigned int i = 0; i < SIZE * SIZE; ++i)
            {
                unsigned int input = 0;
                cin >> input;
                inputs.push_back(input);
            }

//            inputs={2,5,12,16,7,1,3,6,11,14,8,15,4,9,10,13};
            //inputs={1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,15};
//            inputs={1,2,3,4,9,6,7,8,5,16,12,11,14,13,15,10};
            if (!is_misssing_num(inputs)){
                return g_board.init(inputs);//vastanottaa vektori, ja palauttaa ture
            }
            else{
                return false;
            }
        }
        cout << "Unknown choice: " << init_mode << std::endl;
    }
    return true;  // This should never be reached
}

bool is_right_operation(const string& operation){
    if(operation=="w" || operation=="s" || operation=="a" || operation=="d"){
        return true;
    }
    else{
        cout<<"Unknown command: "<<operation<<endl;
        return false;
    }
}

bool is_1to15(unsigned int& luku){
    for(unsigned int i=1; i<16; ++i){
        if(luku==i){
            return true;
        }
    }
    cout<<"Invalid number: "<<luku<<endl;
    return false;
}

int main()
{
    Board game_board; 
    if(!init_board(game_board))
    {
        return EXIT_FAILURE;
    }

    if(!game_board.is_solvable()){
        cout<<"Game is not solvable. What a pity."<<endl;
        return EXIT_SUCCESS;
    }

    game_board.print();

    while(!game_board.is_win()){
        string operation="";
        unsigned int luku=0;
        cout<<"Dir (command, number): ";
        cin>>operation;
        if (operation=="q"){
            return EXIT_SUCCESS;
        }
        cin>>luku;

        if (is_right_operation(operation)&& is_1to15(luku)){
            game_board.move(operation, luku);
        }
        game_board.print();


    }
    // More functionality

    cout<<"You won!"<<endl;
    return EXIT_SUCCESS;
}
