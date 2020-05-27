#include <iostream>
#include<cmath>
#include<iomanip>
using namespace std;

int main()
{
    int kantaluku=0;
    cout<<"Enter a number: ";
    cin>>kantaluku;
    int tulos=kantaluku*kantaluku*kantaluku;
    if ((not(tulos<0))&&(pow(tulos,1.0/3)-kantaluku<=0.001)){
        cout<<"The cube of "<<kantaluku<<" is "<<tulos<<"."<<endl;

    }
    else{
        cout<<"Error! The cube of "<<kantaluku<<" is not "<<tulos<<"."<<endl;
    }


}
