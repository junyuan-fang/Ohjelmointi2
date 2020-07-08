#include "cards.hh"
#include <iostream>
using namespace std;
// A dynamic structure must have a constructor
// that initializes the top item as nullptr.
Cards::Cards(): top_(nullptr){
}

// A dynamic data structure must have a destructor
// that can be called to deallocate memory,
// when the data structure is not needed any more.
Cards::~Cards(){
    while(top_!=nullptr){
        Card_data* item_to_be_delete=top_;
        top_=top_->next;
        delete item_to_be_delete;
    }
}

// Adds a new card with the given id as the topmost element.
void Cards::add(int id){
    if(top_==nullptr){
        Card_data* new_element= new Card_data{id, nullptr};
        top_=new_element;
    }
    else{
        top_=new Card_data{id,top_};
    }
}

// Prints the content of the data structure with ordinal numbers to the
// output stream given as a parameter starting from the first element.
void Cards::print_from_top_to_bottom(std::ostream& s){
    int num=1;
    Card_data* item_print= top_;
    while (item_print!=nullptr){
        s<<num<<": ";
        s<<item_print->data<<endl;
        item_print=item_print->next;
        ++num;
    }
}

//checking empty or not
bool Cards::is_empty(){
    if(top_==nullptr){
        return true;
    }
    else{
        return false;
    }
}

// Removes the topmost card and passes it in the reference parameter id to the caller.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::remove(int& id){
    if(is_empty()||top_->next==nullptr){
        return false;
    }
    else{
        Card_data* item_to_remove= top_;
        id=top_->data;
        top_=top_->next;
        delete item_to_remove;
        return true;
    }
}


// Moves the last element of the data structure as the first one.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::bottom_to_top(){
    if(is_empty()){
        return false;
    }
    else{
        Card_data* item_ptr= top_;
        int id=0;
        int length=1;

        while(item_ptr->next!=nullptr){
            item_ptr=item_ptr->next;
            ++length;
        }
        item_ptr= top_;

        if(length>=2){
            while (item_ptr->next!=nullptr){
                id=item_ptr->next->data;
                if(item_ptr->next->next==nullptr){
                    item_ptr->next=nullptr;
                }
                else{
                    item_ptr=item_ptr->next;
                }
            }
            delete item_ptr->next;
            top_=new Card_data {id, top_};
        }

    }
    return true;
}
// Moves the first element of the data structure as the last one.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::top_to_bottom(){
    int id=0;
    if(remove(id)){
        Card_data* new_structure=new Card_data{id,nullptr};
        Card_data* item= top_;
        while (item->next!=nullptr){
            item=item->next;
        }
        item->next=new_structure;
        return true;
    }
    else{
        return false;
    }
}

int Cards:: recursive_print(Card_data* top, std::ostream& s){

    if (top->next==nullptr){
        s<<1<<": "<<top->data<<endl;
        return 2;
    }
    else{
        int value=top->data;
        int num=0;
        top=top->next;
        num=recursive_print(top,s);
        s<<num<<": "<<value<<endl;
        return ++num;
    }
}

// Prints the content of the data structure with ordinal numbers to the
// output stream given as a parameter starting from the last element.
void Cards:: print_from_bottom_to_top(std::ostream& s){
    Card_data* recursive= top_;
    recursive_print(recursive,s);

}






