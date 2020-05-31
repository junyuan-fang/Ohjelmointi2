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

void encryption(string key, string& txt){
    //tee lista, jossa loytyy ASCII:n arvo 'a-z'-merkijonon merkki
//    cout<<key<<endl;
//    cout<<txt<<endl;       ?
//    for (char kirjain='a';kirjain<='z';++kirjain){
//        char char_key=key.at(i);

//        for (int i=0;i<26;++i){
//            if (kirjain=='a'+i){
//                cout<<kirjain<<" kirjain"<<endl;
//                cout<<char_key<<" key"<<endl;
//                int way=kirjain-char_key;

//                cout<<"way "<<way<<endl;


//                for (int w=0;w<txt.length();++w){
//                    char char_txt=txt.at(w);
//                    if(char_txt==char_key){
//                        cout<<"chartxt "<<char_txt<<endl;
//                        //cout<< static_cast<char>(txt.at(w)+way)<<endl;
//                        txt.at(w)+=way;
//                        cout<<"new txt.at(w) "<<txt.at(w)<<endl;
//                        cout<<endl;

//                    }
//                }
//            }
//        }
//    }
    int i=0;
    string encry_txt=string(txt.length(),'0');
//    for (int i=0; i<26; ++i){
//        encry_txt.insert(0,0);
//    }
    for (char aakkonen='a'; aakkonen<='z';++aakkonen){
        string :: size_type k_indeksi=0;
        string :: size_type k_siirtaa=0;
        k_indeksi=key.find(aakkonen);
        k_siirtaa=k_indeksi-i;
        char korvaava=aakkonen+k_siirtaa;

        int txtpituus=txt.length();
        for (int w=0; w<txtpituus; ++w){
//            if (encry_txt.at(w)=='0'){
                if(txt.at(w)==aakkonen){
                    encry_txt.replace(w,1,string(1,korvaava));
                    for (int i=0; i<26; ++i){
                        if (txt.at(i)==korvaava){
                            encry_txt.replace(txt.find(string(1,korvaava)),1,string(1,aakkonen));
                        }
                    }

//                }
            }
        }
        ++i;
    }




    cout<<"Encrypted text: "<<encry_txt<<endl;


}



int main()
{
    string::size_type pituus=0;
    string key;
    cout << "Enter the encryption key: ";
    cin>>key;
//    key="abcdefghijklmnopqrstuvwzyx";
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
//        txt="thismessageisnotreallyencryptedtoomuch";
        encryption(key,txt);
    }


    return 0;
}
