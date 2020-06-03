#ifndef PLAYER_HH
#include <string>
// PLAYER_HH
using namespace std;

class Player
{
public:
    Player(string name);
    string get_name() const;
    void add_points(int pts);
    bool has_won();
    int get_points() const;
private:
    string name_;
    int pts_;

};

#endif // PLAYER_HH
