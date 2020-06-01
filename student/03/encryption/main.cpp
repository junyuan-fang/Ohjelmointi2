#include <iostream>
#include <string>
#include <cctype>
#include <deque>

using namespace std;

int pituus_virhe(int const& pituus){
    if (pituus !=26){
        cout<<"Error! The encryption key must contain 26 characters."<<endl;
        return EXIT_FAILURE;
    }else{
          return EXIT_SUCCESS;
        }
}

int pienaakkoisia(string const& key){
    //key merkkijonossa ei muuta, vain  a-z
    //eli jokaisen merkkijonon alkion vastaan loytyy ainakin kirjaimen a-z
    for (int i=0;i<26;i++){
        int loyty=0;
        for(char kirjain2='a';kirjain2<='z';++kirjain2 ){
            if (key.at(i)==kirjain2){
                loyty=1;
            }
        }
        if (loyty!=1){
            cout<<"Error! The encryption key must contain only lower case characters."<<endl;
            return 1;
        }
    }
    
    //Merkkijono sisältää kaikki angliset pienaakkoset
    //a-z kirjaimen yksi kerrallaan vastaa ainakin yksi merkijonon alkion
    for(char kirjain='a'; kirjain<='z'; ++kirjain){
        int loyty=0;
        for (int i=0;i<26;i++){
            if(kirjain==key.at(i)) {
               loyty=1;
            }
        }
        if (loyty!=1){
            cout<<"Error! The encryption key must contain all alphabets a-z."<<endl;
            return 1;
        }
    }
    return 0;
}

void encryption(string key, string txt){
    string encrypted_txt="";
    string :: size_type indeksi=0;
    int pituus=txt.length();
    for (int i=0; i<pituus; ++i){
        char txt_char=txt.at(i);
        indeksi=static_cast<int>(txt_char-'a');
        encrypted_txt+=key.at(indeksi);
    }
    cout<<"Encrypted text: "<<encrypted_txt<<endl;


}



int main()
{
    string::size_type pituus=0;
    string key;
    cout << "Enter the encryption key: ";
    cin>>key;
    pituus=key.length();
    if (pituus_virhe(pituus)==1){
        return 1;
    }
    else if (pienaakkoisia(key)==1){
        return 1;
    }
    else{
        string txt;
        cout<<"Enter the text to be encrypted: ";
        cin>>txt;
        encryption(key,txt);
    }
    return 0;
}
