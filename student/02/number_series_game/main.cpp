#include <iostream>
using namespace std;
int main()
{
    int input;
    cout << "How many numbers would you like to have? ";
    cin >>input;
    for (int i=1; i< input+1;i++){
        if (i%3==0){
            cout<<"zip"<<endl;
        }
        else{
          cout<<i<<endl;
        }

    }


}
