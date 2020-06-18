#include <iostream>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

using namespace std;

void print_vertical(unsigned int num)
{
    RECURSIVE_FUNC
    // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
    string num_str=to_string(num);
    if((num<=9)){
        cout<<num<<endl;
    }
    else{
        cout<<num_str.at(0)<<endl;
        unsigned int substruction=num_str.at(0)-48;
        for(int i =1; i<(int)num_str.length();++i){
            substruction*=10;
        }
        if((num-substruction)<=9){
            cout<<"0"<<endl;
//            for(int i=0;i<(int)num_str.length()-1;++i){
//                cout<<"0"<<endl;
//            }
        }
        return print_vertical(num-substruction);
    }


    // Add your implementation here
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    unsigned int number = 0;
    cout << "Enter a number: ";
    cin >> number;
    cout << "The given number (" << number << ") written vertically:" << endl;
    print_vertical(number);
    return 0;
}
#endif
