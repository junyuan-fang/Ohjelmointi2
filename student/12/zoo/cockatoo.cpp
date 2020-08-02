#include "cockatoo.hh"

Cockatoo::Cockatoo():
    Bird(){

}

void Cockatoo::sing(std::ostream& output)const{
    output<<"Kee-ow kee-ow!"<<std::endl;
}
