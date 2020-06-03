
#include <cstdlib>
#include <iostream>
#include <string>
#include "player.hh"

Player::Player(string name):
name_(name),pts_(0){
}

string Player::get_name() const{
    return name_;
}

int Player::get_points() const{
    return pts_;
}

void Player::add_points(int pts){
    pts_+=pts;
}
bool Player::has_won(){
    if (pts_>50){
        pts_=25;
        return false;
    }
    else if (pts_==50){
        return true;
    }
    else {
        return false;
    }
}
