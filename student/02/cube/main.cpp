#include <iostream>
#include<cmath>
using namespace std;

int main()
{
    int kantaluku=0;
    cout<<"Enter a number: ";
    cin>>kantaluku;
    int tulos=kantaluku*kantaluku*kantaluku;

    if ((not(tulos<0))&&(pow(tulos,1.0/3)==kantaluku)){
        cout<<"The cube of 2 is "<<tulos<<"."<<endl;

    }
    else{
        cout<<"Error! The cube of "<<kantaluku<<" is not "<<tulos<<"."<<endl;
    }


}
