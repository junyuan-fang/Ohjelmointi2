#include <iostream>
#include <memory>
#include "cards.hh"

using namespace std;
Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

// Reverses the content of the data structure as opposite.
void Cards::reverse(){
    int item_size=1;
    int id=0;
    int target=0;
    shared_ptr<Card_data> item_before;
    shared_ptr<Card_data> item =top_;
    if(item!=nullptr){//not empty
        while(item->next!=nullptr){
            ++item_size;
            item=item->next;
        }
        target=item->data;
    }
    if (item_size>1){
        while(top_->data!=target){
            item_before=nullptr;
            item=top_;//alustus siirron jalkeen
            if(item->next->data==target){
                id=item->data;
                top_=item->next;
                while(item->next!=nullptr){
                    item=item->next;
                }
                item->next=make_shared<Card_data>(Card_data{id,nullptr});
            }
            else{
                while(item->next->data!=target){
                    //tavoite on siirtaa toka vika kappale viimeiseksi

                    item_before=item;
                    item=item->next;
                }
                //if(item->next->data==target){
                id=item->data;
                item_before->next=item->next;//item_before has been used
                item_before=item;//for pointing current item

                while(item->next!=nullptr){
                    item=item->next;
                }
                item->next=make_shared <Card_data>(Card_data{id,nullptr});
                //}
            }


        }

    }
}
// Removes the topmost card and passes it in the reference parameter id to the caller.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::remove(int& id){
    if(top_==nullptr){
        return false;
    }
    else{
        id=top_->data;
        top_=top_->next;
        return true;
    }
}

// Tip for writing code more efficiently:
// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file cards.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in cards.cpp
