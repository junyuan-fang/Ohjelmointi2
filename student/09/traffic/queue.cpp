#include "queue.hh"
#include <iostream>
using namespace std;

// Implement the member functions of Queue here
// Constructor that initializes the attribute cycle_.
// (The other attibutes are initialized in the private part below.)
Queue::Queue(unsigned int cycle): cycle_(cycle){
}

// Destructor that deletes all the remaining vehicles from the queue.
Queue::~Queue(){
    while(first_!=nullptr){
        Vehicle* item_deletable = first_;
        first_=first_->next;
        delete item_deletable;
    }
}

// Inserts a vehicle, the register number of which is reg, to the queue.
void Queue::enqueue(string reg){
    if(!is_green_){
        Vehicle* new_item_ptr = new Vehicle{reg,nullptr};
        if(first_==nullptr){
            first_= new_item_ptr;
            last_=new_item_ptr;
        }
        else{
            last_->next=new_item_ptr;//because last_ and first_ point the same thing
            last_=new_item_ptr;
        }
    }
    else{
        passable_left_--;
        cout<<"GREEN: The vehicle "<<reg<<" need not stop to wait"<<endl;
        if(passable_left_==0){
               is_green_=!is_green_;
        }
    }
}

// Switches the color of traffic light from green to red or vice versa.
// If the new color is green, lets at least <cycle_> vehicles
// go on (i.e. calls dequeue at least <cycle_> times), and finally
// resets the color to red again.
void Queue::switch_light(){
    // Switches the color of traffic light from green to red or vice versa.
    is_green_=!is_green_;
    // If the new color is green, lets at least <cycle_> vehicles
    // go on (i.e. calls dequeue at least <cycle_> times), and finally
    // resets the color to red again.

    if(is_green_){
        cout<<"GREEN: ";
        unsigned int vehicle_passed=0;
        if(first_==nullptr){
            cout<<"No vehicles waiting in traffic lights"<<endl;
            passable_left_=cycle_;
        }
        else{
            while (vehicle_passed<cycle_&&first_!=nullptr){
                Vehicle* item_delete=first_;
                cout<<first_->reg_num<<" ";

                ++vehicle_passed;
                first_=first_->next;

                //delete former pointer's storage
                delete item_delete;
            }
            cout<<"can go on"<<endl;
            is_green_=!is_green_;//become red
        }

    }
    else{
        cout<<"RED: No vehicles waiting in traffic lights"<<endl;
    }


}



// Resets the attribute cycle_.
void Queue::reset_cycle(unsigned int cycle){
    cycle_=cycle;
}




// Prints the color of traffic light and the register numbers of those
// cars that are waiting in the traffic light queue (if any).
void Queue::print(){
    string light="";
    if(is_green_){
        light="GREEN";
    }
    else{
        light="RED";
    }

    cout<<light<<": ";

    if(first_==nullptr){//if queue is empty
        cout<<"No vehicles ";
    }
    else{
        cout<<"Vehicle(s) ";
        Vehicle* item_ptr= first_;
        while(item_ptr!=nullptr){
            cout<<item_ptr->reg_num<<" ";
            item_ptr=item_ptr->next;
        }
    }
    cout<<"waiting in traffic lights"<<endl;
}
