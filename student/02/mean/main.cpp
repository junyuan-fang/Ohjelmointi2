#include <iostream>
using namespace std;
// Write here a function counting the mean value

int main()
{
    int kertoja = 0;
    float sum= 0;

    cout << "From how many integer numbers you want to count the mean value? ";
    cin >> kertoja;

    if (kertoja>0){
        int i = 0;
        while (i<kertoja){
            int input_value;
            cout<<"Input "<<i+1<<". number: ";
            cin>>input_value;
            sum+=input_value;
            i++;
        }
        float keskiarvo= sum/kertoja;
        cout<<"Mean value of the given numbers is "<<keskiarvo<<endl;

    }else {
        cout<<"Cannot count mean value from "<< kertoja <<" numbers"<<endl;
        }
}


