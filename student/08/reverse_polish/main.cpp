#include <iostream>
using namespace std;
int main(){
    char i;
    int integer;
    int array[10];
    int* osoitin=array;
    int index=0;
    int operators=0;

    cout<<"Input an expression in reverse Polish notation (end with #):"<<endl;
    cout<<"EXPR> ";

    while (cin>>i&&i!='#'){
        if (index==0 && !isdigit(i)){
            cout<<"Error: Expression must start with a number"<<endl;
            exit(1);
        }
        if(isdigit(i)){
            cin.putback(i);
            cin>>integer;
            *osoitin=integer;
        }
        else{
            operators++;

            if (i=='+'){
                *(osoitin-2)=*(osoitin-2)+*(osoitin-1);
                osoitin-=2;
            }
            else if (i=='-'){
                *(osoitin-2)=*(osoitin-2)-*(osoitin-1);
                osoitin-=2;
            }
            else if (i=='*'){
                *(osoitin-2)=*(osoitin-2)**(osoitin-1);
                osoitin-=2;
            }
            else if (i=='/'){
                if(*(osoitin-1)==0){
                    cout<<"Error: Division by zero"<<endl;
                    exit(1);
                }
                else{
                    *(osoitin-2)=*(osoitin-2)/ *(osoitin-1);
                    osoitin-=2;
                }
            }
            else{
                cout<<"Error: Unknown character"<<endl;
                exit(1);
            }
        }
        ++osoitin;
        ++index;
    }
    if(index-2*operators<1){
        cout<<"Error: Too few operands"<<endl;
        exit(1);
    }

    else if (index-2*operators>1){
        cout<<"Error: Too few operators"<<endl;
        exit(1);
    }
    cout<<"Correct: "<<*(osoitin-1)<<" is the result"<<endl;


    return 0;

}


