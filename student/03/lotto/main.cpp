#include <iostream>
#include <string>

using namespace std;

unsigned long int  kertoma(int luku);

//kayttaa kertoman funtkiota, ja muodostaa kombinaatio.
unsigned long int kombinaatio(int pallo, int drawn){
    unsigned long int kombinaatio=1;

    kombinaatio=kertoma(pallo)/(kertoma(pallo-drawn)*kertoma(drawn));
    return kombinaatio;
}

//laske kertomia kombinaatiota varten
unsigned long int kertoma(int luku){
    //for (int tulos=1; luku>0; --luku)
    unsigned long int tulos=1;
    while(luku>0){
        tulos=tulos*luku;
        --luku;
        //cout<<tulos<<endl;
    }
    //cout<<endl;
    return tulos;
}

int main()
{
    int pallo;
    cout << "Enter the total number of lottery balls: ";
    cin >>pallo;

    int drawn;
    cout<<"Enter the number of drawn balls: ";
    cin>>drawn;

    if ((pallo<0)||(drawn<0)){
        cout<<"The number of balls must be a positive number."<<endl;
    }

    else{
        cout<<"The probability of guessing all "
           <<drawn<<" balls correctly is 1/"<<kombinaatio(pallo, drawn)<<endl;
    }
    return 0;
}
